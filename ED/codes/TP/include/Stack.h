#ifndef STACK_H
#define STACK_H

// Declaração de exceções personalizadas para a classe Stack
class stack_overflow_e {};
class empty_stack_e {};

/**
 * @brief Uma classe para representar uma pilha genérica que pode armazenar elementos de qualquer tipo.
 */
template <class T>
class Stack {
    private:
        int length;                         /**< Comprimento atual da pilha */
        static const int MAXLEN = 1e6+10;   /**< Tamanho máximo da pilha */
        T itens[MAXLEN];                    /**< Array para armazenar os itens da pilha */
    public:
        /**
         * @brief Construtor padrão da pilha.
         */
        Stack();

        /**
         * @brief Verifica se a pilha está vazia.
         * @return True se a pilha estiver vazia, False caso contrário.
         */
        bool empty();

        /**
         * @brief Insere um item no topo da pilha.
         * @param item - O item a ser inserido na pilha.
         */
        void push(T item);

        /**
         * @brief Retorna o item no topo da pilha.
         * @return O item no topo da pilha.
         */
        T top();

        /**
         * @brief Remove e retorna o item no topo da pilha.
         * @return O item removido do topo da pilha.
         */
        T pop();

        /**
         * @brief Limpa a pilha, redefinindo seu comprimento para 0.
         */
        void clear();
};

#endif


