#ifndef FORMA3D_H
#define FORMA3D_H

#include "forma.h"

class Forma3D: public Forma {
    public:
        Forma3D(std::string cor);
        virtual double get_volume() = 0;
};

#endif
