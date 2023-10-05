#ifndef QUADRO_ALOCACAO_H
#define QUADRO_ALOCACAO_H
#include <map>
#include <string>
#include <vector>
#include "Disciplina.hpp"

class QuadroAlocacao{
    private:
        std::map<std::string,Disciplina> _lista_aloc;

    public:
        void inserir_alocacao(std::string codigo, std::string nome, std::string dia, std::string horario, std::string sala);
        void remover_alocacao_disciplina(std::string codigo, std::string horario);
        std::vector<Disciplina> recuperar_disciplinas_mais_ofertadas();
        void imprimir_alocacao_completa();
};

#endif
