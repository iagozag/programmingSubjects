#ifndef FORMA2D_H
#define FORMA2D_H

#include "forma.h"

class Forma2D: public Forma {
    public:
        Forma2D(std::string cor);
        virtual double get_area() = 0;
        virtual double get_perimetro() = 0;
};

#endif
