#ifndef CIRCULO_H
#define CIRCULO_H

#include <math.h>
#include "forma2d.h"

class Circulo: public Forma2D {
    private:
        double _raio;
    public:
        Circulo(std::string cor, double _raio);
        std::string get_nome() override;
        double get_area() override;
        double get_perimetro() override;
};

#endif
