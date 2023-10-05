#include <iostream>
#include <algorithm>
#include <vector>
#include "../include/ListaProcessos.hpp"
using namespace std;

bool ordem_prioridade(Processo i,Processo j) { return (i.get_prioridade() > j.get_prioridade()); }

void ListaProcessos::adicionar_processo(Processo proc){
    _lista.push_back(proc);
    sort(_lista.begin(), _lista.end(), ordem_prioridade);
}

Processo ListaProcessos::remover_processo_maior_prioridade(){
    Processo maior_prioridade = _lista.at(0);
    _lista.erase(_lista.begin());
    return maior_prioridade;
}

Processo ListaProcessos::remover_processo_menor_prioridade(){
    Processo menor_prioridade = _lista.at(_lista.size() - 1);
    _lista.pop_back();
    return menor_prioridade;
}

Processo ListaProcessos::remover_processo_por_id(int id){
    Processo id_removido = Processo(0, "", 0);
    for(unsigned i = 0; i < _lista.size(); i++){
        if(_lista.at(i).get_id() == id){
            id_removido = _lista.at(i);
            _lista.erase(_lista.begin()+i);
            return id_removido;
        }
    } 
    return(id_removido);
}

void ListaProcessos::imprimir_lista(){
    for(Processo p: _lista) p.imprimir_dados();
}
