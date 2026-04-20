import glob
import re
import statistics
from urllib.parse import urlparse
from collections import Counter
from bs4 import BeautifulSoup
from warcio.archiveiterator import ArchiveIterator

def analyze_corpus(file_pattern="corpus_*.warc.gz"):
    # Find all WARC files matching the pattern
    warc_files = glob.glob(file_pattern)
    
    if not warc_files:
        print(f"No files found matching pattern: {file_pattern}")
        return

    pages_per_domain = Counter()
    tokens_per_page = []
    total_pages = 0

    print(f"Found {len(warc_files)} WARC file(s). Starting analysis...\n")

    for file_path in warc_files:
        print(f"Processing: {file_path}")
        try:
            with open(file_path, 'rb') as stream:
                for record in ArchiveIterator(stream):
                    # Your crawler saves records as 'resource'
                    if record.rec_type == 'resource':
                        url = record.rec_headers.get_header('WARC-Target-URI')
                        if not url:
                            continue

                        # Extract Domain
                        domain = urlparse(url).netloc
                        if not domain:
                            continue
                        
                        pages_per_domain[domain] += 1
                        total_pages += 1

                        # Extract Text and Count Tokens
                        content = record.content_stream().read()
                        
                        # Use BeautifulSoup to remove HTML tags and scripts
                        soup = BeautifulSoup(content, 'html.parser')
                        
                        # Remove script and style elements for accurate text tokenization
                        for script in soup(["script", "style"]):
                            script.extract()
                            
                        text = soup.get_text(separator=' ', strip=True)
                        
                        # Tokenize by splitting on whitespace
                        tokens = text.split()
                        token_count = len(tokens)
                        
                        tokens_per_page.append(token_count)
                        
        except Exception as e:
            print(f"Error reading {file_path}: {e}")

    print("\n" + "="*50)
    print("CORPUS STATISTICS REPORT")
    print("="*50)

    # 1. Total number of unique domains
    total_unique_domains = len(pages_per_domain)
    print(f"\n1. Total Unique Domains: {total_unique_domains}")
    print(f"   Total Webpages Crawled: {total_pages}")

    # 2. Size distribution (webpages per domain)
    print("\n2. Size Distribution (Top 20 Domains by Webpage Count):")
    for domain, count in pages_per_domain.most_common(20):
        percentage = (count / total_pages) * 100
        print(f"   - {domain}: {count} pages ({percentage:.2f}%)")

    # 3. Size distribution (tokens per webpage)
    if tokens_per_page:
        print("\n3. Size Distribution (Tokens per Webpage):")
        print(f"   - Minimum tokens on a page: {min(tokens_per_page)}")
        print(f"   - Maximum tokens on a page: {max(tokens_per_page)}")
        print(f"   - Average (Mean) tokens per page: {statistics.mean(tokens_per_page):.2f}")
        print(f"   - Median tokens per page: {statistics.median(tokens_per_page):.2f}")
        
        # Optional: Provide a rough distribution breakdown
        ranges = {"0-500": 0, "501-1000": 0, "1001-5000": 0, "5000+": 0}
        for count in tokens_per_page:
            if count <= 500: ranges["0-500"] += 1
            elif count <= 1000: ranges["501-1000"] += 1
            elif count <= 5000: ranges["1001-5000"] += 1
            else: ranges["5000+"] += 1
            
        print("\n   Token Distribution Buckets:")
        for r, count in ranges.items():
            pct = (count / total_pages) * 100
            print(f"   - {r} tokens: {count} pages ({pct:.2f}%)")
    else:
        print("\n3. Size Distribution (Tokens per Webpage): No text data extracted.")

if __name__ == "__main__":
    analyze_corpus()