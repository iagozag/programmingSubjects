#ifndef CUBO_H
#define CUBO_H

#include "forma3d.h"

class Cubo: public Forma3D {
    private:
        double _lado;
    public:
        Cubo(std::string cor, double lado);
        std::string get_nome() override;
        double get_volume() override;
};

#endif


