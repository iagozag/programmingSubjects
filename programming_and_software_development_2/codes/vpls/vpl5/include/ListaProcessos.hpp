#ifndef LISTA_PROCESSOS_H
#define LISTA_PROCESSOS_H
#include <string>
#include <vector>
#include "Processo.hpp"

class ListaProcessos{
    private:
        std::vector<Processo> _lista;

    public:
        void adicionar_processo(Processo proc);
        Processo remover_processo_maior_prioridade();
        Processo remover_processo_menor_prioridade();
        Processo remover_processo_por_id(int id);
        void imprimir_lista();
};

#endif
