#ifndef PDS2_SISTEMA_H
#define PDS2_SISTEMA_H

#include <map>
#include <string>

#include "cliente.h"
#include "frota.h"

class cliente_ja_existe_e {};
class cliente_nao_existe_e {};
class sem_saldo_e {};
class impossivel_alterar_preco_negativo_e {};

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
        /*
         * @brief Constrói um sistema com um preço padrão 5.
         */
        Sistema();

        /*
         * @brief Constrói um sistema com o preço dado.
         * @throws Lança uma exceção se o preço a ser alterado for zero ou negativo. 
         */
        Sistema(double preco_corrida);

        /*
         * @brief Destrói o sistema apagando os clientes criados no heap.
         */
        ~Sistema();

        /*
         * @brief Adiciona carro na frota do sistema.
         *        o id dos carros tem que ser únicos,
         *        mas caso não, uma exceção é lançada.
         */
        void adicionar_carro(std::string cor, unsigned int id);

        /*
         * @brief Cadastra cliente no sistema.
         * @throws Lança uma exceção se o cliente dado já estiver cadastrado. 
         */
        Cliente *cadastra_cliente(std::string nome);

        /*
         * @brief Busca um carro e aloca para o cliente. 
         * @throws Lança uma exceção se o cliente não existe.
         *         Lança uma exceção se o saldo for negativo ou insuficiente.
         */
        Carro *busca_uber(std::string nome);
};

#endif
