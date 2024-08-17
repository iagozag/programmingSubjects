#include "../include/cache.h"

// constroi a cache
Cache::Cache(int _cacheSize, int _lineSize, int _associativity): 
    cacheSize(_cacheSize), 
    lineSize(_lineSize), 
    associativity(_associativity){
    numLines = cacheSize/lineSize;
    numSets = numLines/associativity;
    cache = vector<vector<CacheLine>>(numSets, vector<CacheLine>(associativity, {0, 0}));
    next = vector<int>(numSets);
}

// roda simulacao
void Cache::run(const string &inpFile, const string &outFile) {
    ifstream inp(inpFile);
    ofstream out(outFile);

    string s;
    ui hits = 0, misses = 0;

    while(getline(inp, s)) { // lendo as linhas do arquivo de entrada
        ui address = stoul(s, nullptr, 16);
        ui tag = address >> ((int)log2(lineSize));
        ui setIdx = tag%numSets;

        bool hit = false;
        // itera nas linhas do grupo de índice 'setIdx' e verifica se a linha já existe
        for(auto &cl: cache[setIdx]) if(cl.val and cl.tag == tag){
            hit = true;
            break;
        }

        if(hit) hits++;
        else{
            misses++;

            // prenche se tem espaco vazio
            if(next[setIdx] < associativity)
                cache[setIdx][next[setIdx]] = {true, tag}, q.push(next[setIdx]++);
            // substitui usando First In First Out
            else{
                int trade = q.front(); q.pop();
                cache[setIdx][trade] = {true, tag};
                q.push(trade);
            }
            
            printCache(out);
        }
    }

    out << endl;
    out << "#hits: " << hits << endl;
    out << "#miss: " << misses << endl;
}

void Cache::printCache(ofstream &out) {
    out << "================" << endl;
    out << "IDX V ** ADDR **" << endl;
    for(int i = 0; i < numSets; i++)
        for (int j = 0; j < associativity; j++){
            int idx = i*associativity+j;
            out << setw(3) << setfill('0') << idx << " " << cache[i][j].val;
            if(cache[i][j].val)
                out << " 0x" << hex << uppercase << setw(8) << setfill('0') << cache[i][j].tag << dec;
            out << endl;
        }
}
