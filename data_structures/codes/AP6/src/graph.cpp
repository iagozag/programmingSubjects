#include "../include/Graph.hpp"

Grafo::Grafo(){
    
}

Grafo::~Grafo(){
    
}

void Grafo::InsereVertice(){
    vertices.aumentaTam();
}

void Grafo::InsereAresta(int v, int w){
    vertices.adicionaAresta(v, w);
}

int Grafo::QuantidadeVertices(){
    return vertices.getTam();
}

int Grafo::QuantidadeArestas(){
    return vertices.getArestas();
}

int Grafo::GrauMinimo(){
    return vertices.menorGrau();
}

int Grafo::GrauMaximo(){
    return vertices.maiorGrau();
}

void Grafo::ImprimeVizinhos(int v){
    vertices.imprime(v);
}
