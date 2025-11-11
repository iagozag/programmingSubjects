#include "../include/Disciplina.hpp"
using namespace std;

Disciplina::Disciplina(string codigo, string nome){
    _codigo = codigo;
    _nome = nome;
}

string Disciplina::get_codigo(){
    return _codigo;
}

string Disciplina::get_nome(){
    return _nome;
}

int Disciplina::get_size(){
    return _alocacoes.size();
}

void Disciplina::inserir_alocacao(string dia, string horario, string sala){
    _alocacoes.insert(
        pair<string, Alocacao>(horario, Alocacao(dia, horario, sala))
    );
}

void Disciplina::remover_alocacao(string horario){
    _alocacoes.erase(horario);
}

void Disciplina::imprimir_alocacao(){
    for(auto aloc: _alocacoes){
        cout << _codigo << " " << _nome << " ";
        aloc.second.imprimir_dados();
    }
}

