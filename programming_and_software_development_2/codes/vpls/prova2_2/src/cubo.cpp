#include "../include/cubo.h"

Cubo::Cubo(
    std::string cor,
    double lado
): Forma3D(cor),
   _lado(lado) {
    if(lado <= 0) throw valor_negativo_e();
}

std::string Cubo::get_nome(){
    return "cubo";
}

double Cubo::get_volume(){
    return _lado * _lado * _lado;
}
