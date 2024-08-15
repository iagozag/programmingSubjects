#include "../include/cache.h"

int main(int argc, char *argv[]) {
    // avisa caso a entrada esteja errada
    if (argc != 5) {
        cerr << "Entrada deve ser da seguinte forma: " << endl << "./main <tamanho_total_cache> <tamanho_linha> <tamanho_grupo> <arquivo_entrada>" << endl;
        exit(0);
    }
    
    // define cache
    Cache cache(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]));

    // roda simulação
    cache.run(argv[4], "output.txt");

    exit(0); 
}
