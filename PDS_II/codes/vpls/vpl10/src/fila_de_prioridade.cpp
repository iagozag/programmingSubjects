#include "../include/fila_de_prioridade.h"
#include <utility>
#include <vector>

using namespace std;

struct No{
    pair<string,int> data; 
    No *proximo;
};

FilaDePrioridade::FilaDePrioridade(){
    _primeiro = nullptr;
    _tamanho = 0;
}

string FilaDePrioridade::primeiro() const{
    return(_primeiro->data.first);
}

int FilaDePrioridade::tamanho() const{
    return _tamanho;
}

bool FilaDePrioridade::vazia() const{
    return(tamanho() == 0);
}

void FilaDePrioridade::RemoverPrimeiro(){
    No* atual = _primeiro;
    _primeiro = atual->proximo;

    _tamanho--;
    delete atual;
}

void FilaDePrioridade::Inserir(int p, string s){
    No *novo = new No();
    novo->data = pair<string,int>(s, p);
    novo->proximo = nullptr;

    if (_primeiro == nullptr) {
        _primeiro = novo;
        _tamanho++;
        return;
    }

    No* anterior = nullptr;
    No* atual = _primeiro;
    while(atual != nullptr && atual->data.second >= p){
        anterior = atual;
        atual = atual->proximo;
    }

    if(anterior == nullptr){
        novo->proximo = _primeiro;
        _primeiro = novo;
    } else{
        anterior->proximo = novo;
        novo->proximo = atual;
    }

    _tamanho++;
}

void FilaDePrioridade::Limpar(){
    while(!vazia()){
        RemoverPrimeiro();
    }
}
