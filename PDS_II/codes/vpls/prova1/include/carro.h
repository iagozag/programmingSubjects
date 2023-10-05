#ifndef PDS2_CARRO_H
#define PDS2_CARRO_H

#include <string>

/*
 * Implementa um carro. Cada carro no nosso sistema tem uma cor, um 
 * identificador único. Além disso, existe um booleano indicado se o carro
 * está ocupado.
 *
 * TODO: ALGUMAS (ou TODAS) de suas tarefas aqui:
 *   1. Adicionar o identificador único do mesmo.
 *      1.a. adicione campos se necessário.
 *   2. Mudar o construtor para tal receber tal identificador.
 *   3. Ajustar bugs e memory leaks caso existam
 */
class Carro {
    private:
        unsigned _id;
        std::string _cor;
        bool _ocupado;
    public:
        /*
         * Constroi um carro recbendo sua cor e seu identificador
         */
        Carro(std::string cor, unsigned id);
        
        /*
         * @brief pega a cor de um carro.
         */
        std::string get_cor();
        
        /*
         * @brief pega o identificador único.
         */
        unsigned int get_id();

        /*
         * @brief seta que o carro está ocupado
         */
        void seta_ocupado();
        
        /*
         * @brief indica se um carro está ocupado
         */
        bool ocupado();
};

#endif
