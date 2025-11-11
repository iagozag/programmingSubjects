#ifndef OVERNIGHT_PACKAGE_H
#define OVERNIGHT_PACKAGE_H

#include "package.h"

class OverNightPackage: public Package {
    private:
        int _tx_kg;
    public:
        OverNightPackage(int kg, int custo, int tx_kg, std::string nome, std::string endereco);
        ~OverNightPackage();
        double calculate_cost() override;
};

#endif


