import os
import sys
import json
import time
import psutil
import argparse
import heapq
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
import nltk
from nltk.corpus import stopwords
from nltk.stem.snowball import SnowballStemmer
import gc
import re


def write_merged_term(out_f, term, postings, lexicon, stats):
    # skip empty terms
    if term is None:
        return
        
    # mark byte offset for O(1) disk lookups later
    offset = out_f.tell()
    
    # sort postings strictly by doc_id for daat matching
    final_list = sorted(postings)
    
    # write json array to file
    out_f.write(json.dumps(final_list) + '\n')
    
    # update lexicon and global stats
    lexicon[term] = {"offset": offset, "df": len(final_list)}
    stats['num_lists'] += 1
    stats['total_postings'] += len(final_list)

def cleanup_partial_files(partial_files):
    # print("Merge complete. Cleaning up partial files...", file=sys.stderr)

    # remove temporary disk files
    for f in partial_files:
        os.remove(f)

def merge_partials_external(partial_files, index_dir):
    # print(f"\nStarting merge of {len(partial_files)} partial files...", file=sys.stderr)
    
    lexicon = {}
    stats = {'num_lists': 0, 'total_postings': 0}
    inverted_index_path = os.path.join(index_dir, "postings.jsonl")
    
    # open all files simultaneously for reading
    file_handles = [open(f, 'r', encoding='utf-8') for f in partial_files]
    
    try:
        # open final target file
        with open(inverted_index_path, 'w', encoding='utf-8') as out_f:
            cur_term = None
            cur_postings = []
            
            # sort files lexicographically 
            for line in heapq.merge(*file_handles):
                # separate term from json
                term, postings_json = line.split('\t', 1)
                postings = json.loads(postings_json)
                
                # if term changes, flush the previous term to disk
                if term != cur_term:
                    write_merged_term(out_f, cur_term, cur_postings, lexicon, stats)
                    cur_term = term
                    cur_postings = postings
                else:
                    # accumulate postings for the same term
                    cur_postings.extend(postings)
                    
            # write the last term to disk
            write_merged_term(out_f, cur_term, cur_postings, lexicon, stats)
            
    finally:
        # guarantee all handles close even if an error occurs
        for fh in file_handles:
            fh.close()
            
    # delete partials
    cleanup_partial_files(partial_files)
    
    num_lists = stats['num_lists']
    avg_list_size = stats['total_postings'] / num_lists
    
    return num_lists, avg_list_size, lexicon


class Indexer:
    def __init__(self, mem_limit_mb, corpus_path, index_dir):
        # convert mb to bytes
        self.mem_limit = mem_limit_mb * 1024 * 1024
        self.corpus_path = corpus_path
        self.index_dir = index_dir
        self.stemmer = SnowballStemmer("english")
        self.stop_words = set(stopwords.words("english"))
        
        # inverted index
        self.local_index = defaultdict(list)
        self.doc_lengths_path = os.path.join(self.index_dir, "doc_lengths.tsv")
        self.partial_files = []
        
        # cooldown to prevent flushing all the time
        self.docs_since_last_flush = 0
        
        # create output directory if missing
        if not os.path.exists(self.index_dir):
            os.makedirs(self.index_dir)
            
    def check_memory(self):
        # get current ram usage
        cur_mem = psutil.Process(os.getpid()).memory_info().rss

        # trigger only if over 95% and processed "enough" docs
        return cur_mem > (self.mem_limit * 0.95) and self.docs_since_last_flush >= 100000

    def parse(self, line):
        # load json
        doc = json.loads(line)
        doc_id = str(doc.get("id", ""))
        
        # get all text
        text = " ".join(filter(None, [
            doc.get("title", ""), 
            doc.get("text", ""), 
            " ".join(doc.get("keywords", []))
        ]))

        # preserve unicode letters but destroy punctuation (!, /, -, etc)
        text = re.sub(r'[^\w\s]', ' ', text)
        text = text.lower()

        return doc_id, text

    def process_document(self, line):
        # parses the text lines
        doc_id, text = self.parse(line)
        
        # tokenization via nltk
        tokens = nltk.word_tokenize(text)
        term_counts = defaultdict(int)
        doc_length = 0
        
        # filter and stem each token
        for token in tokens:
            if token.isalnum() and token not in self.stop_words:
                stemmed = self.stemmer.stem(token)
                term_counts[stemmed] += 1
                doc_length += 1
                
        return doc_id, term_counts, doc_length

    def flush_to_disk(self):
        # skip if nothing to flush
        if not self.local_index:
            return
            
        # generate partial filename
        partial_path = os.path.join(self.index_dir, f"partial_{len(self.partial_files)}.tsv")
        
        # get postings and write them to partial file
        with open(partial_path, 'w', encoding='utf-8') as f:
            for term in sorted(self.local_index.keys()):
                postings = sorted(self.local_index[term])
                f.write(f"{term}\t{json.dumps(postings)}\n")
        
        # track the flushed file
        self.partial_files.append(partial_path)

        # free memory
        self.local_index.clear()

        # force garbage collector to return ram to os
        gc.collect()

        # reset the cooldown counter
        self.docs_since_last_flush = 0

    def process_corpus(self):
        # batch documents to maximize threading efficiency
        batch_size = 5000
        batch = []
        docs_processed = 0
        
        # print(f"Starting document parsing and tokenization...", file=sys.stderr)
        
        # open disk stream for document data
        with open(self.doc_lengths_path, 'w', encoding='utf-8') as dl_file:
            with open(self.corpus_path, 'r', encoding='utf-8') as f:

                # initialize thread pool for parallel parsing with 5 threads
                with ThreadPoolExecutor(max_workers=5) as executor:
                    while True:
                        line = f.readline()
                        if line:
                            batch.append(line)
                        
                        # process when batch is full or end of file is reached
                        if len(batch) >= batch_size or (not line and batch):
                            futures = [executor.submit(self.process_document, doc_line) for doc_line in batch]
                            
                            # gather completed threads
                            for future in as_completed(futures):
                                doc_id, term_counts, doc_length = future.result()
                                
                                # append doc data to disk
                                dl_file.write(f"{doc_id}\t{doc_length}\n")
                                
                                # populate memory index with tuples
                                for term, tf in term_counts.items():
                                    self.local_index[term].append((doc_id, tf))
                                    
                            # update metrics
                            docs_processed += len(batch)
                            self.docs_since_last_flush += len(batch) 
                            
                            # print(f"\rProcessed {docs_processed} documents...", end="", file=sys.stderr)
                            
                            # reset the batch
                            batch = []
                            
                            # if run out of memory, flush to disk
                            if self.check_memory():
                                self.flush_to_disk()
                                
                        # break loop if corpus is finished
                        if not line:
                            break

        # print(f"\nFinished parsing {docs_processed} documents.", file=sys.stderr)

        # flush remaining items in ram
        self.flush_to_disk()

    def get_doc_stats(self):
        # variables to compute average document length
        N = 0
        total_dl = 0
        final_doc_lengths = {}
        
        # read streamed data back into memory
        with open(self.doc_lengths_path, 'r', encoding='utf-8') as dl_file:
            for line in dl_file:
                doc_id, length = line.strip().split('\t')
                length = int(length)
                final_doc_lengths[doc_id] = length
                N += 1
                total_dl += length

        # assemble document stats dictionary
        doc_stats = {
            "lengths": final_doc_lengths,
            "N": N,
            "avg_dl": total_dl / N
        }
        
        # write final data json
        with open(os.path.join(self.index_dir, "doc_stats.json"), 'w') as f:
            json.dump(doc_stats, f)

        # remove the temporary tsv file
        os.remove(self.doc_lengths_path)

    def get_statistics(self, start_time, num_lists, avg_list_size):
        # compute total execution time
        elapsed_time = time.time() - start_time
        
        # aggregate total size of all output files
        index_size_mb = sum(os.path.getsize(os.path.join(self.index_dir, f)) for f in os.listdir(self.index_dir)) / (1024 * 1024)
        
        # construct final stats as a json
        stats = {
            "Index Size": round(index_size_mb, 2),
            "Elapsed Time": round(elapsed_time, 2),
            "Number of Lists": num_lists,
            "Average List Size": round(avg_list_size, 2)
        }
        
        # print(f"Indexing complete!\n", file=sys.stderr)
        print(json.dumps(stats, indent=4))

    def build(self):
        # mark start time for benchmarking
        start_time = time.time()
        
        # parse all docs and generate temporary index parts
        self.process_corpus()
        
        # merge temporary index parts
        num_lists, avg_list_size, lexicon = merge_partials_external(self.partial_files, self.index_dir)
        
        # print(f"Writing final lexicon...", file=sys.stderr)

        # dump the lexicon dictionary mapping terms to bytes
        with open(os.path.join(self.index_dir, "lexicon.json"), 'w') as f:
            json.dump(lexicon, f)
            
        # calculate document metrics
        self.get_doc_stats()
        
        # output benchmark metrics
        self.get_statistics(start_time, num_lists, avg_list_size)


if __name__ == "__main__":
    # parse command line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("-m", type=int, required=True, help="Memory available in MB")
    parser.add_argument("-c", type=str, required=True, help="Path to corpus file")
    parser.add_argument("-i", type=str, required=True, help="Path to index directory")
    args = parser.parse_args()

    indexer = Indexer(args.m, args.c, args.i)
    indexer.build()
