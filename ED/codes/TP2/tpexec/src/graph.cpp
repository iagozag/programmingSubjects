#include "../include/graph.h"
#include <iostream>
using namespace std;

Graph::Graph(int length): adjList(length){
    _length = length;
    colors = new int[_length];
}

Graph::~Graph(){
    delete[] colors;
}

void Graph::insertEdge(int v, int w){
    adjList.addEdge(v, w);
}

int Graph::getColor(int x){
    return colors[x];
}

void Graph::addColors(int v[]){
    for (int i = 0; i < _length; i++)
        colors[i] = v[i];
}

bool Graph::verify_coloring(){
    int N = _length;
    for(int i = 0; i < N; i++){
        int E = adjList.degree(i);
        int sum = 0, color = getColor(i), arr[color-1];
        for(int j = 0; j < color-1; j++) arr[j] = 0;

        NodeType* vert = adjList.getEdges(i, 0);

        for(int j = 0; j < E; j++){
            int vert = adjList.getEdges(i, j), curColor = getColor(vert);
            if(curColor < color && !arr[curColor-1]) sum += curColor, arr[curColor-1] = 1;
        }

        if(sum != (color*(color-1))/2) return false;
    }

    return true;
}

