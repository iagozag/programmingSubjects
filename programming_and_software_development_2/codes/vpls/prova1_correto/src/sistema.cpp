#include "../include/sistema.h"

Sistema::Sistema() {
    _preco_corrida = 5;
}

Sistema::Sistema(double preco_corrida) {
    if(preco_corrida <= 0)
        throw impossivel_alterar_preco_negativo_e();

    _preco_corrida = preco_corrida;
}

Sistema::~Sistema(){
    for(auto cliente: _clientes)
        delete cliente.second;
}

Cliente *Sistema::cadastra_cliente(std::string nome) {
    if (_clientes.count(nome) > 0)
        throw cliente_ja_existe_e();

    Cliente *cliente = new Cliente(nome);
    _clientes[nome] = cliente;
    return cliente;
}

void Sistema::adicionar_carro(std::string cor, unsigned int id) {
    _frota.cadastrar_carro(cor, id);
}

Carro *Sistema::busca_uber(std::string nome) {
    if (_clientes.count(nome) == 0)
        throw cliente_nao_existe_e();

    Cliente *c = _clientes.at(nome);

    if (c->get_saldo() == 0 || c->get_saldo() < _preco_corrida)
        throw sem_saldo_e();

    Carro *car = _frota.alocar_carro();
    c->remover_saldo(_preco_corrida);

    _carros_alocados.insert(std::pair<unsigned int,std::string>(car->get_id(),nome));

    return car;
}
