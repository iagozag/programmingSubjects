#ifndef HEAP_HPP
#define HEAP_HPP

#include "../include/unionFind.hpp"

class Heap{

    public:
        Heap(int maxsize);
        ~Heap();

        void Inserir(Aresta a);
        Aresta Remover();

        //Retorna true caso o heap esteja vazio, false caso contrário.
        bool Vazio();

    private:
        int GetAncestral(int posicao);
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);

        int tamanho;
        Aresta* data;
};


#endif
