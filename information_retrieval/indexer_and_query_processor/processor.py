import os
import argparse
import json
import math
import nltk
from nltk.corpus import stopwords
from nltk.stem.snowball import SnowballStemmer
import re


class QueryProcessor:
    def __init__(self, index_dir, ranker):
        self.index_dir = index_dir
        self.ranker = ranker.upper()
        self.stemmer = SnowballStemmer("english")
        self.stop_words = set(stopwords.words('english'))
        
        # load required index structures into memory
        self.load_data(index_dir)

    def load_data(self, index_dir):
        # load lexicon containing term offsets and document frequencies
        with open(os.path.join(index_dir, "lexicon.json"), 'r') as f:
            self.lexicon = json.load(f)
            
        # load document lengths and stats
        with open(os.path.join(index_dir, "doc_stats.json"), 'r') as f:
            stats = json.load(f)
            self.doc_lengths = stats["lengths"]
            self.N = stats["N"]
            self.avg_dl = stats["avg_dl"]

    def preprocess_query(self, query):
        # preserve unicode letters but destroy punctuation (!, /, -, etc)
        query = re.sub(r'[^\w\s]', ' ', query)

        # tokenize text
        tokens = nltk.word_tokenize(query.lower())
        terms = []
        
        # filter and stem each token
        for token in tokens:
            if token.isalnum() and token not in self.stop_words:
                terms.append(self.stemmer.stem(token))
                
        # return list of unique terms
        return list(set(terms))

    def fetch_postings(self, term):
        # return empty list if term is unknown
        if term not in self.lexicon:
            return []
            
        # get byte offset from lexicon
        offset = self.lexicon[term]["offset"]
        
        # jump directly to the offset and read the json array
        with open(os.path.join(self.index_dir, "postings.jsonl"), 'r', encoding='utf-8') as f:
            f.seek(offset)
            line = f.readline()
            return json.loads(line)

    def calculate_bm25(self, tf, df, dl):
        # bm25 parameters
        k1 = 1.2
        b = 0.75
        
        # calculate inverse document frequency
        idf = math.log((self.N - df + 0.5) / (df + 0.5) + 1.0)
        
        # calculate term frequency component
        term_score = idf * (tf * (k1 + 1)) / (tf + k1 * (1 - b + b * (dl / self.avg_dl)))
        return term_score

    def calculate_tfidf(self, tf, df):
        # standard tf-idf implementation
        tf_idf_score = (1 + math.log(tf)) * math.log(self.N / (df + 1))
        return tf_idf_score

    def calculate_score(self, doc_id, term_tfs, dfs):
        # initialize base score
        score = 0.0
        dl = self.doc_lengths.get(doc_id, self.avg_dl)
        
        # accumulate score for each term
        for term, tf in term_tfs.items():
            df = dfs[term]
            
            if self.ranker == "BM25":
                score += self.calculate_bm25(tf, df, dl)
            elif self.ranker == "TFIDF":
                score += self.calculate_tfidf(tf, df)
                
        return score

    def daat_match(self, query_terms):
        postings = {}
        dfs = {}
        
        # load all required posting lists
        for term in query_terms:
            lst = self.fetch_postings(term)
            
            # conjunctive rule: if any term is missing, zero results
            if not lst: 
                return [] 
                
            postings[term] = lst
            dfs[term] = self.lexicon[term]["df"]
            
        # initialize pointers for daat tracking
        ptrs = {term: 0 for term in query_terms}
        results = []
        
        while True:
            # check if any pointer reached the end of its list
            if any(ptrs[term] >= len(postings[term]) for term in query_terms):
                break
                
            # get the current document ids under each pointer
            current_docs = {term: postings[term][ptrs[term]][0] for term in query_terms}
            max_doc = max(current_docs.values())
            
            # check if all pointers are on the exact same document
            if all(doc == max_doc for doc in current_docs.values()):

                # match found: collect term frequencies and compute score
                term_tfs = {term: postings[term][ptrs[term]][1] for term in query_terms}
                score = self.calculate_score(max_doc, term_tfs, dfs)
                results.append({"ID": max_doc, "Score": round(score, 4)})
                
                # advance all pointers to evaluate the next document
                for term in query_terms:
                    ptrs[term] += 1
            else:
                # advance pointers that are lagging behind the max_doc
                for term in query_terms:
                    while ptrs[term] < len(postings[term]) and postings[term][ptrs[term]][0] < max_doc:
                        ptrs[term] += 1

        # sort by score descending and return top 10
        results.sort(key=lambda x: x["Score"], reverse=True)
        return results[:10]

    def process_single_query(self, query):
        # extract and clean query terms
        query_terms = self.preprocess_query(query)
        
        # execute matching algorithm
        if not query_terms:
            results = []
        else:
            results = self.daat_match(query_terms)
            
        # construct structured output
        output = {
            "Query": query,
            "Results": results
        }
        return output

    def process_queries(self, queries_path):
        # read and process queries line by line
        with open(queries_path, 'r', encoding='utf-8') as f:
            for line in f:
                query = line.strip()
                
                # skip empty lines
                if not query: 
                    continue
                
                # process query and format to json
                output = self.process_single_query(query)
                print(json.dumps(output, indent=4))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", type=str, required=True, help="Path to index directory")
    parser.add_argument("-q", type=str, required=True, help="Path to queries file")
    parser.add_argument("-r", type=str, choices=["TFIDF", "BM25"], required=True, help="Ranking function")
    args = parser.parse_args()

    processor = QueryProcessor(args.i, args.r)
    processor.process_queries(args.q)
