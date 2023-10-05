#ifndef FORMA_H
#define FORMA_H

#include <string>

class valor_negativo_e {};

class Forma {
    private:
        std::string _cor;
    public:
        Forma(std::string cor);
        virtual std::string get_nome() = 0;
        std::string get_cor();
};

#endif
