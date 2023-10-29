#include "../include/graph.h"
#include <iostream>
using namespace std;

Grafo::Grafo(int tamanho){
    _tamanho = tamanho;
    lista = new ListaAdjacencia(_tamanho);
    colors = new int[_tamanho];
}

Grafo::~Grafo(){
    delete lista;
    delete[] colors;
}

void Grafo::InsereAresta(int v, int w){
    lista->adicionaAresta(v, w);
}

int Grafo::QuantidadeVertices(){
    return lista->getTam();
}

int Grafo::getCor(int x){
    return colors[x];
}

void Grafo::adicionaCores(int v[]){
    colors = v;
}

void Grafo::ImprimeVizinhos(int v){
    lista->imprime(v);
}

bool Grafo::verify_coloring(){
    for(int i = 0; i < _tamanho; i++){
        int E = lista->getArestas(i).getLength();
        int arr[E]; int sum = 0;
        fill(arr, arr+E, 0);

        for(int j = 0; j < E; j++){
            int vert = lista->getArestas(i).at(j);
            if(!arr[vert]) sum += getCor(vert), arr[vert] = 1;
        }
    }

    return true;
}

