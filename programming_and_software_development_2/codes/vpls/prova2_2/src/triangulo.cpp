#include <cstdarg>

#include "../include/triangulo.h"

Triangulo::Triangulo(
    std::string cor,
    double l1,
    double l2,
    double l3
): Forma2D(cor) {
    if(l1 <= 0 || l2 <= 0 || l3 <= 0) throw valor_negativo_e();

    _lados.push_back(l1);
    _lados.push_back(l2);
    _lados.push_back(l3);
}

double Triangulo::get_area(){
    double p = get_perimetro()/2;
    return sqrt(p * (p - _lados.at(0)) * (p - _lados.at(1)) * (p - _lados.at(2)));
}
double Triangulo::get_perimetro(){
    double soma = 0;
    for(double l: _lados) soma += l;

    return soma;
}

std::string Triangulo::get_nome(){
    return "triangulo";
}
