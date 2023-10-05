#ifndef DISCIPLINA_H
#define DISCIPLINA_H
#include <algorithm>
#include <map>
#include <vector>
#include "Alocacao.hpp"

class Disciplina{
    private:
        std::string _codigo, _nome;
        std::map<std::string, Alocacao> _alocacoes;

    public:
        Disciplina(std::string codigo, std::string nome);
        std::string get_codigo();
        std::string get_nome();
        int get_size();
        void inserir_alocacao(std::string dia, std::string horario, std::string sala);
        void remover_alocacao(std::string horario);
        void imprimir_alocacao();
};

#endif
