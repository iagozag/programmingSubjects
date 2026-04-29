import sys
import argparse
from queue import Queue, Empty
import requests
from bs4 import BeautifulSoup
from url_normalize import url_normalize
from urllib.parse import urljoin, urlparse
import threading
from concurrent.futures import ThreadPoolExecutor, as_completed
from protego import Protego
import time
import json
import io
from warcio.warcwriter import WARCWriter
from warcio.statusandheaders import StatusAndHeaders


# parses command line arguments
def getArgs():
    parser = argparse.ArgumentParser(description="A web crawler implementation.")
    parser.add_argument('-s', "--seeds", required=True, help="Path to the file containing seed URLs")
    parser.add_argument('-n', "--limit", type=int, default=100000, help="Limit for the number of pages to crawl")
    parser.add_argument('-d', "--debug", action="store_true", help="Enable debug mode")
    args = parser.parse_args()
    return args.seeds, args.limit, args.debug


class Crawler:
    def __init__(self):
        # variables and locks

        # to not visit same urls
        self.visited_urls = set()
        self.visited_lock = threading.Lock()

        # number of successfully crawled and saved HTML pages
        self.crawl_cnt = 0
        self.cnt_lock = threading.Lock()

        # to parse robots.txt rules and track the last access time per domain.
        self.domain_rules = {}
        self.domain_last_accessed = {}
        self.politeness_lock = threading.Lock()

        # to write in corpus file
        self.warc_lock = threading.Lock()
        self.cur_warc_file = None
        self.corpus = None

        # headers to mimic a standard browser, preventing 403 Forbidden errors from basic bot-protection.
        self.HEADERS = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36',
            'Accept-Language': 'en-US,en;q=0.9,pt-BR;q=0.8,pt;q=0.7',
            'DNT': '1'
        }

    # fetches and parses robots.txt for a given domain if it hasn't been cached yet.
    def politeness(self, domain, debug_mode):
        needs_fetch = False

        # verify if current url robots.txt file was already parsed
        with self.politeness_lock:
            if domain not in self.domain_rules:
                self.domain_rules[domain] = Protego.parse("")
                self.domain_last_accessed[domain] = 0
                needs_fetch = True

        if needs_fetch:
            # parse robots.txt with headers to prevent being blocked
            robots_url = urljoin(domain, "/robots.txt")
            try:
                robots_response = requests.get(robots_url, headers=self.HEADERS, timeout=30)
                if robots_response.status_code == 200:
                    rp = Protego.parse(robots_response.text)

                    # update the cache with the actual parsed rules
                    with self.politeness_lock:
                        self.domain_rules[domain] = rp
            except Exception as e:
                if debug_mode:
                    print(f"Robots.txt fetch failed for {domain}: {e}")


    # politeness policy sections explicits that an url must not be visited twice in less then 100ms
    # this function is used to obey the established delay
    def wait_delay(self, rp, domain):
        crawl_delay = rp.crawl_delay("*")
        if crawl_delay is None:
            crawl_delay = 0.1

        # calculate required sleep time inside the lock, and immediately reserve our future access time.
        sleep_time = 0
        with self.politeness_lock:
            time_since_last = time.time() - self.domain_last_accessed.get(domain, 0)
            if time_since_last < crawl_delay:
                sleep_time = crawl_delay - time_since_last
            self.domain_last_accessed[domain] = time.time() + sleep_time

        if sleep_time > 0:
            time.sleep(sleep_time)


    # corpus need to be updated every 1000 pages crawled
    # so, if current number of crawled pages is divisible for 1000, we need to close current corpus file and start a new one
    def reset_warc_file_if_needed(self):
        # if it is not divisible
        if self.crawl_cnt % 1000 != 0:
            return

        # close current file
        if self.cur_warc_file:
            self.cur_warc_file.close()

        # create a new one
        file_idx = self.crawl_cnt // 1000
        filename = f"corpus_{file_idx:03d}.warc.gz"
        self.cur_warc_file = open(filename, "wb")
        self.corpus = WARCWriter(self.cur_warc_file, gzip=True)


    # create debug json record for debug mode
    # contains: page url, title, text and timestamp
    def get_debug_content(self, soup, url):
        title_tag = soup.find('title')
        title = title_tag.string.strip() if title_tag and title_tag.string else ""
        timestamp = time.time()
        text = soup.get_text(separator=' ', strip=True)
        text_list = ' '.join(text.split()[:20])
        webpage = {
            "URL": url,
            "Title": title,
            "Text": text_list,
            "Timestamp": int(timestamp)
        }
        return json.dumps(webpage)



    def crawler(self, frontier, limit, debug_mode):
        while True:
            # verify if number of crawler pages exceeded the user limit
            with self.cnt_lock:
                if self.crawl_cnt >= limit:
                    break

            # get page from frontier
            try:
                url = frontier.get(timeout=30)
            except Empty:
                break

            try:
                # split url into its components
                parsed_url = urlparse(url)
                domain = f"{parsed_url.scheme}://{parsed_url.netloc}"

                # skip malformed URLs that lack a scheme or network location
                if not parsed_url.scheme or not parsed_url.netloc:
                    continue

                # ensure rules are cached for this domain
                self.politeness(domain, debug_mode)

                with self.politeness_lock:
                    rp = self.domain_rules[domain]

                # verify if current url path is allowed by robots.txt
                if not rp.can_fetch(url, "*"):
                    if debug_mode:
                        print(f"[{threading.current_thread().name}] Blocked by robots.txt: {url}")
                    continue

                # wait delay
                self.wait_delay(rp, domain)

                if debug_mode:
                    print(f"[{threading.current_thread().name}] Fetching: {url}")

                # execute the HTTP GET request
                response = requests.get(url, headers=self.HEADERS, timeout=30)

                # only proceed if the request was successful (HTTP 200 OK)
                if response.status_code == 200:
                    content_type = response.headers.get('Content-Type', '')
                    if 'text/html' not in content_type:     # we must only follow discovered links to HTML pages
                        continue

                    # write data to corpus
                    with self.warc_lock:
                        self.reset_warc_file_if_needed()
                        with self.cnt_lock:
                            if self.crawl_cnt >= limit:
                                continue
                            self.crawl_cnt += 1
                            print(self.crawl_cnt)

                        record = self.corpus.create_warc_record(
                            url, 
                            'resource', 
                            payload=io.BytesIO(response.content), 
                        )
                        self.corpus.write_record(record)

                    # parse html content using BeautifulSoup lib
                    soup = BeautifulSoup(response.text, "html.parser")

                    # get debug content
                    if debug_mode:
                        webpage_json = self.get_debug_content(soup, url)
                        print(webpage_json)

                    # try to discover new links
                    for link in soup.find_all('a', href=True):
                        # join urls
                        next_url = urljoin(url, link['href'])
                        if next_url.startswith("http"):
                            try:
                                # normalize urls filtering params
                                # Example: print(url_normalize("www.google.com/search?q=test&utm_source=test", filter_params=True))
                                # Output: https://www.google.com/search?q=test
                                next_url_norm = url_normalize(next_url, filter_params=True)

                            except Exception:
                                continue
                            
                            # revisitation policy (only add url to queue if it was not visited yet)
                            with self.visited_lock:
                                if next_url_norm not in self.visited_urls:
                                    self.visited_urls.add(next_url_norm)
                                    frontier.put(next_url_norm)
                else:
                    if debug_mode:
                        print(f"[{threading.current_thread().name}] Failed to fetch {url} - Status: {response.status_code}")

            except requests.RequestException as e:
                if debug_mode:
                    print(f"[{threading.current_thread().name}] Request error fetching {url}: {e}")
            except Exception as e:
                if debug_mode:
                    print(f"[{threading.current_thread().name}] Unexpected error processing {url}: {e}")
            
            finally:
                frontier.task_done()

    def run(self, seeds_path, limit, debug_mode, workers=5):
        # add first urls from seeds file to frontier queue
        frontier = Queue()
        try:
            with open(seeds_path, 'r') as file:
                for line in file:
                    seed_url = line.strip()
                    if seed_url:
                        try:
                            seed_url_norm = url_normalize(seed_url, filter_params=True)
                            self.visited_urls.add(seed_url_norm)
                            frontier.put(seed_url_norm)
                        except Exception as e:
                            print(f"Error normalizing seed {seed_url}: {e}")
        except FileNotFoundError:
            print(f"Error: Could not find the file '{seeds_path}'")
            sys.exit(1)

        # parallelization policy: launch worker threads using a ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=workers) as executor:
            futures = [executor.submit(self.crawler, frontier, limit, debug_mode) for _ in range(workers)]
            
            # monitor futures to surface any fatal unhandled exceptions that kill a thread
            for future in as_completed(futures):
                try:
                    future.result()
                except Exception as e:
                    print(f"Error: Thread crashed {e}")

        # final cleanup
        if self.cur_warc_file:
            self.cur_warc_file.close()

        print(f"Finished crawling! Crawled {self.crawl_cnt} pages.")

def main():
    # get arguments from command line
    seeds_path, limit, debug_mode = getArgs()
    
    # instantiate the crawler class and run it
    crawler = Crawler()
    crawler.run(seeds_path, limit, debug_mode, workers=40)

if __name__ == "__main__":
    main()
