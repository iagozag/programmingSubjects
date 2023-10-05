#ifndef PDS2_SISTEMA_H
#define PDS2_SISTEMA_H

#include <map>
#include <string>

#include "cliente.h"
#include "frota.h"

class cliente_ja_existe_e {};
class cliente_nao_existe_e {};
class sem_saldo_e {};

/*
 * A classe sistema está ok de métodos e tads utilizados. Porém, ainda tem
 * tarefas aqui.
 *
 * TODO: 1. Faça um novo construtor que recebe o preco da corrida.
 *          - Crie uma nova exceção e lançe a mesma se o preço for <= 0.
 *       2. Documentar essa classe.
 *       3. Garantir que não tem bugs nem leaks
 */
class Sistema {
    private:
        std::map<std::string, Cliente *> _clientes;
        std::map<unsigned int, std::string> _carros_alocados;
        Frota _frota;
        double _preco_corrida;
    public:
        Sistema();
        void adicionar_carro(std::string cor, unsigned int id);
        Cliente *cadastra_cliente(std::string nome);
        Carro *busca_uber(std::string nome);
};

#endif
