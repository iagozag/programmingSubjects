#include "../include/twodaypackage.h"

TwoDayPackage::TwoDayPackage(
    int kg,
    int custo,
    int tx_fixa,
    std::string nome,
    std::string endereco
): Package(kg, custo, nome, endereco),
   _tx_fixa(tx_fixa) {
}

TwoDayPackage::~TwoDayPackage() {}

double TwoDayPackage::calculate_cost(){
    return (get_custo()*get_kg() + _tx_fixa);
}
