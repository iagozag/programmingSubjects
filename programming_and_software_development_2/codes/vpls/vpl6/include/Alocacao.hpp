#ifndef ALOCACAO_H
#define ALOCACAO_H
#include <iostream>
#include <string>

class Alocacao{
    private:
        std::string _dia, _horario, _sala;

    public:
        Alocacao(std::string dia, std::string horario, std::string sala);
        std::string get_dia();
        std::string get_horario();
        std::string get_sala();
        void imprimir_dados();
};

#endif
