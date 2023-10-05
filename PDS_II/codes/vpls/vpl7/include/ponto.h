#ifndef PONTO_H
#define PONTO_H

#include <math.h>

class Ponto2D{
    private:
        double _x;
        double _y;

    public:
        Ponto2D(double x = 0, double y = 0);
        double get_x();
        double get_y();
        double calcular_distancia(Ponto2D& ponto);
};

#endif
