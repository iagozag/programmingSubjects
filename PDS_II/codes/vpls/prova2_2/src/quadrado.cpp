#include "../include/quadrado.h"

Quadrado::Quadrado(
    std::string cor,
    double lado
): Forma2D(cor), 
   _lado(lado) {
    if(lado <= 0) throw valor_negativo_e();
}

double Quadrado::get_area(){
    return _lado*_lado;
}
double Quadrado::get_perimetro(){
    return 4*_lado;
}

std::string Quadrado::get_nome(){
    return "quadrado";
}
