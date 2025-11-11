#include <cctype>

#include "celular.hpp"

// TODO: Inicialize aqui sua variavel estatica. Caso tenha optado por essa
// solucao.
int Celular::_cod = 1;

Celular::Celular(std::string modelo,
                 std::string fabricante,
                 int armazenamento,
                 int memoria,
                 double peso,
                 std::string cor,
                 int qtd,
                 float valor):
                 _modelo(modelo),
                 _fabricante(fabricante),
                 _armazenamento(armazenamento),
                 _memoria(memoria),
                 _peso(peso),
                 _cor(cor),
                 _qtd(qtd),
                 _valor(valor),
                 _codigo(_cod)
{
  // TODO: Implemente este metodo
    _cod++;
}

bool Celular::operator<(const Celular& other) const {
  // TODO: Implemente este metodo. 
  // Preste atencao no exemplo que a descricao utilizada na ordenacao considera
  // a fabricante antes do modelo do celular
    if(_fabricante != other._fabricante)
        return _fabricante < other._fabricante;

    return _modelo < other._modelo;
}

bool Celular::operator==(const Celular& other) const{
    return _codigo == other._codigo;
}

bool Celular::operator!=(const Celular& other) const { 
    return !operator==(other); 
}

std::string Celular::get_modelo() const{
    return _modelo;
}

std::string Celular::get_fabricante() const{
    return _fabricante;
}

int Celular::get_armazenamento() const{
    return _armazenamento;
}

int Celular::get_memoria() const{
    return _memoria;
}

double Celular::get_peso() const{
    return _peso;
}

std::string Celular::get_cor() const{
    return _cor;
}

int Celular::get_qtd() const{
    return _qtd;
}

float Celular::get_valor() const{
    return _valor;
}


int Celular::get_codigo() const{
    return _codigo;
}
