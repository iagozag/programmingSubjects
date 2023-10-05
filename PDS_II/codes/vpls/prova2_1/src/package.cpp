#include "../include/package.h"

Package::Package(
    int kg,
    int custo,
    std::string nome,
    std::string endereco
): _nome(nome),
   _endereco(endereco),
   _kg(kg),
   _custo(custo) {
    if(kg <= 0 || custo <= 0) throw valor_negativo_e();
}

Package::~Package() {}

std::string Package::get_nome(){
    return _nome;
}

std::string Package::get_endereco(){
    return _endereco;
}

int Package::get_kg(){
    return _kg;
}

int Package::get_custo(){
    return _custo;
}

double Package::calculate_cost(){
    return _kg*_custo;
}
