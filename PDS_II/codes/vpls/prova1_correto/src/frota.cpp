#include "../include/frota.h"
#include<iostream>

Frota::~Frota(){
    for(auto carro: _carros)
        delete carro;
}

void Frota::cadastrar_carro(std::string cor, unsigned int id) {
    for(auto car: _carros){
        if(car->get_id() == id)
            throw id_ja_existe_e();
    }

    Carro *c = new Carro(cor, id);
    _carros.push_back(c);
}

Carro *Frota::alocar_carro() {
    if (_carros.empty())
        throw zero_carros_disponiveis_e();
   
    unsigned i = 0;
    for(i = 0; i < _carros.size(); i++)
        if(_carros.at(i)->ocupado() == false) break;
    
    _carros.at(i)->seta_ocupado();

    Carro *alocado = _carros.at(i);
    return alocado;
}
