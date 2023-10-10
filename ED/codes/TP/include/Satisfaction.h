#ifndef SATISFACTION_H
#define SATISFACTION_H

#include <string>

/**
 * @brief Classe Pair representa o par de resultados.
 */
class Pair {
    private:
        bool ans;            /**< Valor booleano do par. */
        std::string result;  /**< String resultado associado ao par caso 'ans' seja igual a 1. */

    public:
        /**
         * @brief Construtor padrão da classe Pair.
         */
        Pair();

        /**
         * @return O valor booleano.
         */
        bool get_ans();

        /**
         * @return A string resultado, caso a expressão seja satisfazível e tenha solução única.
         */
        std::string get_res();

        /**
         * @brief Define o valor booleano do par.
         * @param b O valor booleano a ser definido.
         */
        void set_ans(bool b);

        /**
         * @brief Define a string resultado associada ao par.
         * @param result A string a ser definida na classe de resposta.
         */
        void set_result(std::string result);
};

/**
 * @brief Função que avalia a satisfação de uma expressão.
 * @param st A expressão a ser avaliada.
 * @param values Os valores associados aos operandos na expressão.
 * @return Um objeto Pair contendo a resposta. '0' caso a expressão não seja satisfazível, 
 *         '1' e a string resultado caso a expressão com os respectivos valores e quantificadores
 *         seja satisfazível.
 */
Pair satisfaction(std::string& st, std::string& values);

#endif

