#include <iostream>
#include <getopt.h>

#include "../include/Graph.hpp"

using namespace std;

#define BASICVALUES 'd'
#define NEIGHBORHOOD 'n'
#define COMPLETE 'k'

static char opt;

void parse_args(int argc,char** argv){
    int c;

    opt = -1;

    while ((c = getopt(argc, argv, "dnk")) != EOF){
        switch(c) {
            case 'd':
	            opt = BASICVALUES;
                break;
            case 'n':
	            opt = NEIGHBORHOOD;
                break;
            case 'k':
                opt = COMPLETE;
                break;
            default:
                exit(0);
        }
    }
}

int main(int argc, char ** argv){
    parse_args(argc, argv);
    Grafo g;
    int n; cin >> n;

    for(int i = 0; i < n; ++i){
        g.InsereVertice();

        int m; cin >> m;
        for(int j = 0; j < m; j++){
            int a; cin >> a; g.InsereAresta(i, a);
        }
    }

    if(opt == BASICVALUES){
        cout << g.QuantidadeVertices() << "\n"
             << g.QuantidadeArestas() << "\n"
             << g.GrauMinimo() << "\n"
             << g.GrauMaximo() << "\n";
    }
    else if(opt == NEIGHBORHOOD){
        for(int i = 0; i < n; i++)
            g.ImprimeVizinhos(i), cout << "\n";
    }
    else if(opt == COMPLETE){
        cout << (g.GrauMinimo() == n-1) << "\n";  
    }
    else cout << "Comando invalido!" << endl;
      
    exit(0);
}
