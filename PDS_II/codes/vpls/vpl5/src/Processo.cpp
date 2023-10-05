#include <iostream>
#include "../include/Processo.hpp"
using namespace std;

Processo::Processo(int id, string nome, int prioridade){
    _id = id;
    _nome = nome;
    _prioridade = prioridade;
}

int Processo::get_id(){
    return _id;
}

string Processo::get_nome(){
    return _nome;
}

int Processo::get_prioridade(){
    return _prioridade;
}

void Processo::imprimir_dados(){
    cout << _id << "  " << _nome << "  " << _prioridade << "\n";
} 
