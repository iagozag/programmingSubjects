#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <iostream>

/**
 * @brief Classe NodeType representa um nó de lista encadeada para uso em AdjacencyList.
 */
class NodeType {
    public: 
        /**
         * @brief Construtor da classe NodeType.
         */
        NodeType();

        /**
         * @brief Obtém o dado armazenado no nó.
         * @return O dado armazenado no nó.
         */
        int getData();

        /**
         * @brief Obtém o ponteiro para o próximo nó na lista encadeada.
         * @return O ponteiro para o próximo nó.
         */
        NodeType* getNext();

    private:
        int data;       /**< Dado armazenado no nó. */
        NodeType* next; /**< Ponteiro para o próximo nó na lista encadeada. */

    friend class LinkedList;
};

/**
 * @brief Classe LinkedList representa uma lista encadeada para uso em AdjacencyList.
 */
class LinkedList {
    public:
        /**
         * @brief Construtor da classe LinkedList.
         */
        LinkedList();

        /**
         * @brief Destrutor da classe LinkedList.
         */
        ~LinkedList();

        /**
         * @brief Obtém o tamanho da lista.
         * @return O tamanho da lista.
         */
        int getLength();

        /**
         * @brief Verifica se a lista está vazia.
         * @return True se a lista estiver vazia, False caso contrário.
         */
        bool empty();

        /**
         * @brief Insere um item na lista.
         * @param item O item a ser inserido.
         */
        void insert(const int& item);

        /**
         * @brief Obtém o primeiro nó da lista.
         * @return O primeiro nó da lista.
         */
        NodeType* getFirst();

        /**
         * @brief Limpa a lista, liberando a memória alocada.
         */
        void clear();

    private:
        int length;          /**< O comprimento da lista. */
        NodeType* head;      /**< Ponteiro para o início da lista. */
        NodeType* last;      /**< Ponteiro para o último nó na lista. */
};

/**
 * @brief Classe AdjacencyList representa uma lista de adjacência.
 */
class AdjacencyList {
    public:
        /**
         * @brief Construtor da classe AdjacencyList.
         * @param n O tamanho da lista de adjacência.
         */
        AdjacencyList(int n);

        /**
         * @brief Destrutor da classe AdjacencyList.
         */
        ~AdjacencyList();

        /**
         * @brief Obtém o comprimento da lista de adjacência.
         * @return O comprimento da lista de adjacência.
         */
        int getLen();

        /**
         * @brief Obtém o primeiro nó de uma lista de adjacência de um vértice.
         * @param x O índice do vértice.
         * @return O primeiro nó da lista de adjacência.
         */
        NodeType* getFirst(int x);

        /**
         * @brief Adiciona uma aresta entre dois vértices.
         * @param v O primeiro vértice.
         * @param w O segundo vértice.
         */
        void addEdge(int v, int w);

        /**
         * @brief Obtém o grau de um vértice.
         * @param x O vértice a ser avaliado.
         * @return O grau do vértice.
         */
        int degree(int x);

    private:
        LinkedList* list; /**< Array de listas encadeadas para representar a lista de adjacência. */
        int length;       /**< O comprimento da lista de adjacência. */
};

#endif

