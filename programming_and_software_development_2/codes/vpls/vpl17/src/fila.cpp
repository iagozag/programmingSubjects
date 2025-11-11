#include "../include/fila.h"

struct No {
  int chave;
  No* proximo;
};

Fila::Fila() {
    primeiro_ = nullptr;
    ultimo_ = nullptr;
    tamanho_ = 0;
}

void Fila::Inserir(int k) {
    No* novo = new No{k, nullptr};

    if(tamanho() == 0) primeiro_ = novo;
    else ultimo_->proximo = novo;
        
    ultimo_ = novo;
    tamanho_++;
}

void Fila::RemoverPrimeiro() {
    if(tamanho() == 0) 
        throw ExcecaoFilaVazia();

    No* atual = primeiro_;
    primeiro_ = atual->proximo;

    tamanho_--;
    delete atual;
}

int Fila::primeiro() const {
    if(tamanho() == 0) 
        throw ExcecaoFilaVazia();

    return primeiro_->chave;
}

int Fila::ultimo() const {
    if(tamanho() == 0) 
        throw ExcecaoFilaVazia();

    return ultimo_->chave;
}

int Fila::tamanho() const {
    return tamanho_;
}
