#ifndef LISTA_ADJACENCIA_H
#define LISTA_ADJACENCIA_H

#include "LinkedList.hpp"

class ListaAdjacencia {
    public:
        ListaAdjacencia();

        int getTam();
        int getArestas();
        void aumentaTam();
        void adicionaAresta(int v, int w);
        int menorGrau();
        int maiorGrau();
        void imprime(int v);

    private:
        LinkedList<LinkedList<int>> lista;

        int tamanho;
        int arestas;
};

#endif

