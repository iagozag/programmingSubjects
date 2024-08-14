#ifndef CACHE_H
#define CACHE_H

#include <macros.h>

// define a classe da cache
class Cache{
    private:
        struct CacheLine{
            bool val;
            ui tag;
        };

        int cacheSize;
        int lineSize;
        int associativity;
        int numLines;
        int numSets;

        vector<vector<CacheLine>> cache;

        void printCache(ofstream &output);

    public:
        Cache(int _cacheSize, int _lineSize, int _associativity);
        void run(const string &inputFile, const string &outputFile);
};

#endif // CACHE_H
