#include "../include/ListaAdjacencia.hpp"

#include <iostream>
using namespace std;

ListaAdjacencia::ListaAdjacencia(){
    tamanho = 0;
    arestas = 0;
}

int ListaAdjacencia::getTam(){
    return tamanho;
}

int ListaAdjacencia::getArestas(){
    return arestas/2;
}

void ListaAdjacencia::aumentaTam(){
    lista.insert(LinkedList<int>());
    tamanho++;
}

void ListaAdjacencia::adicionaAresta(int v, int w){
    lista.at(v).insert(w);
    arestas++;
}

int ListaAdjacencia::menorGrau(){
    int min = lista.at(0).getLength();
    for(int i = 1; i < tamanho; ++i){
        if(lista.at(i).getLength() < min) min = lista.at(i).getLength();
    }
    
    return min;
}

int ListaAdjacencia::maiorGrau(){
    int max = lista.at(0).getLength();
    for(int i = 1; i < tamanho; ++i){
        if(lista.at(i).getLength() > max) max = lista.at(i).getLength();
    }

    return max;
}

void ListaAdjacencia::imprime(int v){
    lista.at(v).print();
}
