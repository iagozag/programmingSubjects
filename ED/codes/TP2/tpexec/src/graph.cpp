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
    for(int i = 0; i < _length; i++){
        int sum = 0, colorV = getColor(i), vis[colorV-1];
        for(int j = 0; j < colorV-1; j++) vis[j] = 0;

        NodeType* vert = adjList.getFirst(i);
        for(int j = 0; j < adjList.degree(i); j++){
            int curColor = getColor(vert->getData());
            if(curColor < colorV && !vis[curColor-1]) 
                sum += curColor, vis[curColor-1] = 1;

            vert = vert->getNext();
        }

        if(sum != (colorV*(colorV-1))/2) return false;
    }

    return true;
}

