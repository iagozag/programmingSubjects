#include "../include/esfera.h"

Esfera::Esfera(
    std::string cor,
    double raio
): Forma3D(cor),
   _raio(raio) {
    if(raio <= 0) throw valor_negativo_e();
}

std::string Esfera::get_nome(){
    return "esfera";
}

double Esfera::get_volume(){
    return (4.0/3.0) * M_PI * pow(_raio, 3);
}
