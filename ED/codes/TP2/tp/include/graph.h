#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "../include/linked_list.h"

/**
 * @brief Classe Graph representa um grafo e suas operações.
 */
class Graph {
    public:
        /**
         * @brief Construtor da classe Graph.
         * @param length O número de vértices no grafo.
         */
        Graph(int length);

        /**
         * @brief Destrutor da classe Graph.
         */
        ~Graph();

        /**
         * @brief Insere uma aresta entre dois vértices.
         * @param v O primeiro vértice.
         * @param w O segundo vértice.
         */
        void insertEdge(int v, int w);

        /**
         * @brief Adiciona cores aos vértices do grafo.
         * @param v Um array de cores para os vértices.
         */
        void addColors(int* v);

        /**
         * @brief Verifica se a coloração do grafo é válida.
         * @return True se a coloração for válida, False caso contrário.
         */
        bool verify_coloring();
        
    private:
        int _length; /**< O número de vértices no grafo. */
        AdjacencyList adjList; /**< Lista de adjacência para representar o grafo. */
        int* colors; /**< Um array de cores para os vértices. */
};

#endif



