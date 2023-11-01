#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <iostream>

class invalid_pos_e {};

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
        NodeType* getHead();
        int getItem(int pos);
        void clear();

    private:
        int length;
        NodeType* head;
        NodeType* last;
        NodeType* at(int pos);
};

class AdjacencyList {
    public:
        AdjacencyList(int n);
        ~AdjacencyList();

        int getLen();
        void addEdge(int v, int w);
        int degree(int x);
        int getEdges(int x, int y);
        int getColor(int x);
        void setColors(int* v);

    private:
        LinkedList* list;
        int length;
};

#endif
