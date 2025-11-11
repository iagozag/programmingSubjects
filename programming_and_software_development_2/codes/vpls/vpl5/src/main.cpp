#include <iostream>
#include "../include/ListaProcessos.hpp"
using namespace std;

int main(){
    ListaProcessos lista_proc;
    char option;
    int id, prioridade;
    string nome;
    
    while(cin >> option){
        switch(option) {
            case 'a': {
                cin >> id >> nome >> prioridade;
                Processo proc = Processo(id, nome, prioridade);
                lista_proc.adicionar_processo(proc);
                break;
            }
            case 'm': {
                lista_proc.remover_processo_maior_prioridade();
            break;
            }
            case 'n': {
                lista_proc.remover_processo_menor_prioridade();
                break;
            }
            case 'r': {
                cin >> id;
                lista_proc.remover_processo_por_id(id);
                break;
            }
            case 'p': {
                lista_proc.imprimir_lista();
                break;
            }
        
        }
    }

    exit(0);
}
