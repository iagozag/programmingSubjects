#include "../include/graph.h"
#include <iostream>
using namespace std;

Grafo::Grafo(int tamanho): listaAdj(tamanho){
    _tamanho = tamanho;
    colors = new int[_tamanho];
}

Grafo::~Grafo(){
    delete[] colors;
}

void Grafo::InsereAresta(int v, int w){
    listaAdj.adicionaAresta(v, w);
}

int Grafo::QuantidadeVertices(){
    return listaAdj.getTam();
}

int Grafo::getCor(int x){
    return colors[x];
}

void Grafo::adicionaCores(int v[]){
    colors = v;
}

void Grafo::ImprimeVizinhos(int v){
    listaAdj.imprime(v);
}

bool Grafo::verify_coloring(){
    int N = _tamanho;
    for(int i = 0; i < N; i++){
        int E = listaAdj.degree(i);
        int sum = 0, cor = getCor(i), arr[cor-1];
        for(int j = 0; j < cor-1; j++) arr[j] = 0;

        for(int j = 0; j < E; j++){
            int vert = listaAdj.getArestas(i, j), corAtual = getCor(vert);
            if(corAtual < cor && !arr[corAtual-1]) sum += corAtual, arr[corAtual-1] = 1;
        }

        if(sum != (cor*(cor-1))/2) return false;
    }

    return true;
}

