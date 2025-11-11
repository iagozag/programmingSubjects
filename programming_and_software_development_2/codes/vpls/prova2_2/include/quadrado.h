#ifndef QUADRADO_H
#define QUADRADO_H

#include "forma2d.h"

class Quadrado: public Forma2D {
    private:
        double _lado;
    public:
        Quadrado(std::string cor, double lado);
        std::string get_nome() override;
        double get_area() override;
        double get_perimetro() override;
};

#endif
