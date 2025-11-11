#include "../include/forma.h"

Forma::Forma(
    std::string cor
): _cor(cor) {}

std::string Forma::get_cor(){
    return _cor;
}
