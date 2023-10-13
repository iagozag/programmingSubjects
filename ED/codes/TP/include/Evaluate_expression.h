#ifndef EVALUATE_EXPRESSION_H
#define EVALUATE_EXPRESSION_H

#include <string>

/**
 * @brief Função para determinar a prioridade de um operador.
 * @param c O operador a ser avaliado.
 * @return A prioridade do operador (3 para '~', 2 para '&', 1 para '|', -1 para outros).
 */
int priority(char c);

/**
 * @brief Converte uma expressão infixada em uma expressão posfixada.
 * @param st A expressão infixada de entrada.
 * @param values Os valores associados aos operandos na expressão para conversão no posfixo.
 * @return A expressão posfixada resultante.
 */
std::string infix_to_postfix(std::string st, std::string values);

/**
 * @brief Avalia uma expressão lógica em formato posfixado.
 * @param st A expressão posfixada a ser avaliada.
 * @param values Os valores associados aos operandos na expressão.
 * @return O resultado da avaliação (true ou false).
 */
bool evaluate(std::string st, std::string values);

#endif
