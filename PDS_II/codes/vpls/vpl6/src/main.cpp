#include "../include/QuadroAlocacao.hpp"
using namespace std;

int main(){
    QuadroAlocacao quadro;
    char option;
    string codigo, nome, dia, horario, sala;

    while(cin >> option){
        switch (option) {
            case 'a': {
                cin >> codigo >> nome >> dia >> horario >> sala;
                quadro.inserir_alocacao(codigo, nome, dia, horario, sala);
                break;
            }
            case 'm': {
                vector<Disciplina> mais_ofertas = quadro.recuperar_disciplinas_mais_ofertadas();
                for(auto disc: mais_ofertas)
                    disc.imprimir_alocacao();
                break;
            }
            case 'r': {
                cin >> codigo >> horario;
                quadro.remover_alocacao_disciplina(codigo, horario);
                break;
            }
            case 'p': {
                quadro.imprimir_alocacao_completa();
                break;
            }
            case 'b': {
                break;
            }
        }
    }

    exit(0);
}
