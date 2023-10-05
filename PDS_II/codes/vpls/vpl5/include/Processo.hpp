#ifndef PROCESSO_H
#define PROCESSO_H
#include <string>

class Processo{
    private:
        int _id, _prioridade;
        std::string _nome;

    public:
        Processo(int id, std::string nome, int prioridade);
        int get_id();
        std::string get_nome();
        int get_prioridade();
        void imprimir_dados();
};

#endif
