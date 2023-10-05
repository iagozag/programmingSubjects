#include "../include/QuadroAlocacao.hpp"
using namespace std;

void QuadroAlocacao::inserir_alocacao(string codigo, string nome, string dia, string horario, string sala){
    Disciplina disc = Disciplina(codigo, nome);
    disc.inserir_alocacao(dia, horario, sala);

    if(_lista_aloc.count(codigo) > 0){
        _lista_aloc.at(codigo).inserir_alocacao(dia, horario, sala);
        return;
    }
    
   _lista_aloc.insert(pair<string,Disciplina>(codigo, disc)); 
}

void QuadroAlocacao::remover_alocacao_disciplina(string codigo, string horario){
    _lista_aloc.at(codigo).remover_alocacao(horario);
}

vector<Disciplina> QuadroAlocacao::recuperar_disciplinas_mais_ofertadas(){
    vector<Disciplina> mais_ofertas;
    int max_size = 0;
    for(auto disc : _lista_aloc)
        if(max_size < disc.second.get_size()) max_size = disc.second.get_size();

    for(auto disc : _lista_aloc)
        if(max_size == disc.second.get_size()) mais_ofertas.push_back(disc.second);

    return mais_ofertas;
}

void QuadroAlocacao::imprimir_alocacao_completa(){
    for(auto mapa: _lista_aloc){
        mapa.second.imprimir_alocacao();
    }
}
