#ifndef TRIANGULO_H
#define TRIANGULO_H

#include <vector>
#include <math.h>
#include "forma2d.h"

class Triangulo: public Forma2D {
    private:
        std::vector<double> _lados;
    public:
        Triangulo(std::string cor, double l1, double l2, double l3);
        std::string get_nome() override;
        double get_area() override;
        double get_perimetro() override;
};

#endif
