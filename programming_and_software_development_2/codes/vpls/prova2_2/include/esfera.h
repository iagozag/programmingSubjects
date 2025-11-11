#ifndef ESFERA_H
#define ESFERA_H

#include <math.h>
#include "forma3d.h"

class Esfera: public Forma3D {
    private:
        double _raio;
    public:
        Esfera(std::string cor, double raio);
        std::string get_nome() override;
        double get_volume() override;
};

#endif

