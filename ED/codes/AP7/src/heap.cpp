#include "../include/heap.hpp"

#include <iostream>
using namespace std;

Heap::Heap(int maxsize){
    data  = new int[maxsize];
    tamanho = 0;
}

Heap::~Heap(){
    delete data; 
}

void Heap::Inserir(int x){
    data[tamanho] = x;
    int i = tamanho;
    int p = GetAncestral(i);
    while(data[i] < data[p]){
        swap(data[i], data[p]);
        i = p;
        p = GetAncestral(i);
    }
    tamanho++;
}

int Heap::Remover(){
    int x = data[0];
    data[0] = data[tamanho-1];
    tamanho--;

    int i = 0;
    while(1){
        int esq = GetSucessorEsq(i);
        int dir = GetSucessorDir(i);
        int menor = i;

        if(esq < tamanho && data[esq] < data[menor])
            menor = esq;

        if(dir < tamanho && data[dir] < data[menor])
            menor = dir;

        if(menor != i){
            swap(data[i], data[menor]);
            i = menor;
        }
        else break;
    }

    return x;
}

bool Heap::Vazio(){
    return(tamanho == 0);
}

int Heap::GetAncestral(int posicao){
    return (posicao-1)/2;
}

int Heap::GetSucessorEsq(int posicao){
    return 2*posicao+1;
}

int Heap::GetSucessorDir(int posicao){
    return 2*posicao+2;
}
