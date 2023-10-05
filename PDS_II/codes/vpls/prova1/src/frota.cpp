#include "../include/frota.h"

void Frota::cadastrar_carro(std::string cor, unsigned int id) {
    Carro* c = new Carro(cor, id);
    if(std::find(_carros.begin(), _carros.end(), c) != _carros.end()){
        throw id_ja_existe_e();
    }

    _carros.push_back(c);
}

Carro *Frota::alocar_carro() {
    if (_carros.empty())
        throw zero_carros_disponiveis_e();

    int i = 0;
    while(_carros.at(i)->ocupado() == true) i++;

    Carro *alocado = _carros.at(i);
    return alocado;
}
