#ifndef PDS2_CLIENTE_H
#define PDS2_CLIENTE_H

#include <string>

class impossivel_adicionar_saldo_negativo_e {};
class saldo_insuficiente_para_remocao_e {};

/*
 * Implementa um cliente. Cada cliente no nosso sistema tem um saldo e um
 * login.
 *
 * TODO: ALGUMAS (ou TODAS) de suas tarefas aqui:
 *   1. Garantir que o adicionar saldo lança uma exceção.
 *   2. Garantir que o remover saldo lança uma exceção.
 *   3. Ajustar bugs e leaks caso existam
 */
class Cliente {
    private:
        std::string _login;
        double _saldo;
    public:
        /*
         * Constroi um cliente com o login dado
         */
        Cliente(std::string login);
        
        /*
         * @brief Adiciona um saldo ao cliente
         * @throws Lança uma exceção se o saldo a adicionar for negativo.
         */
        void adicionar_saldo(double saldo);
        
        /*
         * @brief Remove um saldo do cliente
         * @throws Lança uma exceção se o cliente não tiver saldo para remover.
         */
        void remover_saldo(double saldo);
        
        /*
         * @brief Pega o saldo atual
         */
        double get_saldo();

        /*
         * @brief Pega o login do cliente
         */     
        std::string get_login();
};

#endif
