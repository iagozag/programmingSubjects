#include "../include/overnightpackage.h"
#include <iostream>

OverNightPackage::OverNightPackage(
    int kg,
    int custo,
    int tx_kg,
    std::string nome,
    std::string endereco
): Package(kg, custo, nome, endereco),
   _tx_kg(tx_kg) {
    if(tx_kg <= 0 || custo <= 0 || kg <= 0) throw valor_negativo_e();
}

OverNightPackage::~OverNightPackage() {}

double OverNightPackage::calculate_cost(){
    return ((get_custo()+_tx_kg)*get_kg());
}

