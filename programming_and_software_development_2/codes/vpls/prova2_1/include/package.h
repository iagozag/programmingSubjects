#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

class valor_negativo_e {};

class Package{
    private:
        std::string _nome;
        std::string _endereco;
        int _kg;
        int _custo;
    public:
        Package(int kg, int custo, std::string nome, std::string endereco);
        virtual ~Package();
        std::string get_nome();
        std::string get_endereco();
        int get_kg();
        int get_custo();
        virtual double calculate_cost();
};

#endif
