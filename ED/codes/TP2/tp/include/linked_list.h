#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <iostream>

class NodeType {
    public: 
        NodeType();
    private:
        int data;
        int cor;
        NodeType* next;

    friend class LinkedList;
};


class LinkedList {
    public:
        LinkedList();
        ~LinkedList();

        int getLength();
        bool empty();
        void insert(const int& item);
        int at(int index);
        NodeType* getHead();
        int getItem(int pos);
        int getHeadVert();
        int getHeadCor();
        void setHead(int v, int c);
        void clear();
        void print() const;

    private:
        int length;
        NodeType* head;
        NodeType* last;
        NodeType* Posiciona(int pos);
};

class ListaAdjacencia {
    public:
        ListaAdjacencia(int n);
        ~ListaAdjacencia();

        int getTam();
        void adicionaAresta(int v, int w);
        int degree(int x);
        int getArestas(int x, int y);
        int getCor(int x);
        void setCores(int* v);
        void imprime(int v);

    private:
        LinkedList* lista;
        int tamanho;
};

#endif
