#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <iostream>

class NodeType {
    int data;
    int color;
    NodeType* next;

    NodeType(const int& value) : data(value), next(nullptr) {}
    friend class LinkedList;
};


class LinkedList {
    public:
        LinkedList() : length(0), head(nullptr), last(nullptr) {}
        ~LinkedList();

        int getLength();
        bool empty();
        void insert(const int& item);
        int& at(int index);
        void clear();
        void print() const;

    private:
        int length;
        NodeType* head;
        NodeType* last;
};

class ListaAdjacencia {
    public:
        ListaAdjacencia(int n);
        ~ListaAdjacencia();

        int getTam();
        void adicionaAresta(int v, int w);
        void imprime(int v);

    private:
        LinkedList* lista;
        int tamanho;
};

#endif
