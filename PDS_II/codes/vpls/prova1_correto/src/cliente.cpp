#include "../include/cliente.h"

Cliente::Cliente(std::string login) {
    _saldo = 0.0;
    _login = login;
}

void Cliente::adicionar_saldo(double saldo) {
    if (saldo < 0)
        throw impossivel_adicionar_saldo_negativo_e();
    
    _saldo += saldo;
}

void Cliente::remover_saldo(double saldo) {
    if (saldo > _saldo)
        throw saldo_insuficiente_para_remocao_e();
    
    _saldo -= saldo;
}

std::string Cliente::get_login() {
    return _login;
}

double Cliente::get_saldo() {
    return _saldo;
}
