#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "../include/linked_list.h"

class Graph{
    public:
        Graph(int length);
        ~Graph();

        void insertEdge(int v, int w);
        void addColors(int* v);
        bool verify_coloring();
        
    private:
        int _length;
        AdjacencyList adjList;
        int* colors;
        
};

#endif

