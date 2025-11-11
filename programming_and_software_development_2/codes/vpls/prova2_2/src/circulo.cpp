#include "../include/circulo.h"

Circulo::Circulo(
    std::string cor,
    double raio
): Forma2D(cor), 
   _raio(raio) {
    if(raio <= 0) throw valor_negativo_e();
}

double Circulo::get_area(){
    return M_PI*_raio*_raio;
}
double Circulo::get_perimetro(){
    return 2*M_PI*_raio;
}

std::string Circulo::get_nome(){
    return "circulo";
}
