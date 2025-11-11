#include "../include/ponto.h"

Ponto2D::Ponto2D(double x, double y){
    _x = x;
    _y = y;
}
       
double Ponto2D::get_x(){
    return _x;
}

double Ponto2D::get_y(){
    return _y;
}

double Ponto2D::calcular_distancia(Ponto2D& ponto){
    return(sqrt((_x - ponto._x) * (_x - ponto._x) + (_y - ponto._y) * (_y - ponto._y)));
}
