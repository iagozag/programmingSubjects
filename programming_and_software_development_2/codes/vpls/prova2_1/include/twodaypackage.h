#ifndef TWO_DAY_PACKAGE_H
#define TWO_DAY_PACKAGE_H

#include "package.h"

class TwoDayPackage: public Package {
    private:
        int _tx_fixa;
    public:
        TwoDayPackage(int kg, int custo, int tx_fixa, std::string nome, std::string endereco);
        ~TwoDayPackage();
        double calculate_cost() override;
};

#endif

