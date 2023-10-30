#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "../include/linked_list.h"

class Grafo{
    public:
        Grafo(int tamanho);
        ~Grafo();

        void InsereAresta(int v, int w);
        int QuantidadeVertices();
        void adicionaCores(int* v);
        int getCor(int x);
        void ImprimeVizinhos(int v);
        bool verify_coloring();
        
    private:
        int _tamanho;
        ListaAdjacencia listaAdj;
        int* colors;
        
};

#endif

