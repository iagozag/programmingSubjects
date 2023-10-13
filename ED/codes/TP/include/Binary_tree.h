#ifndef TREE_H
#define TREE_H

#include <string>

// Classe NodeType representa os nós da árvore binária
class NodeType {
    public:
        /**
         * @brief Construtor padrão da classe NodeType.
         */
        NodeType();

        /**
         * @return O item no nó.
         */
        std::string getItem();

    private:
        std::string item; // O item armazenado no nó
        NodeType *esq;    // Ponteiro para o filho esquerdo
        NodeType *dir;    // Ponteiro para o filho direito

    friend class BinaryTree;
};

// Classe BinaryTree representa uma árvore binária
class BinaryTree {
    public:
        /**
         * @brief Construtor padrão da classe BinaryTree que recebe uma expressão lógica.
         * @param expression A expressão lógica a ser usada na árvore.
         */
        BinaryTree(std::string expression);
        
        /**
         * @brief Destrutor da classe BinaryTree.
         */
        ~BinaryTree();

        /**
         * @return O ponteiro para a raiz da árvore.
         */
        NodeType* get_root();

        /**
         * @brief Insere um item na árvore.
         * @param item O item a ser inserido na árvore.
         */
        void insert(std::string item);

        /**
         * @brief Limpa a árvore, liberando a memória alocada.
         */
        void clear();

        /**
         * @brief Realiza uma travessia pós-ordem na árvore e calcula se a expressão é satisfazível.
         * @param p A raiz da árvore.
         * @return True se a expressão lógica dados quantificadores e valores fixos é satisfazível,
         *         False caso contrário.
         */
        bool posOrder(NodeType *p);

    private:
        /**
         * @brief Função auxiliar para inserção recursiva na árvore.
         * @param p A raiz da árvore.
         * @param item O item a ser inserido na árvore.
         */
        void InsertRecursive(NodeType* &p, std::string item);

        /**
         * @brief Função auxiliar para exclusão recursiva na árvore.
         * @param p A raiz da árvore.
         */
        void DeleteRecursive(NodeType* p);
        
        std::string expression_; // A expressão lógica avaliada na árvore
        NodeType *root; // Ponteiro para a raiz da árvore
};

/**
 * @brief Função para substituir letras 'a' ou 'e' por 0 ou 1.
 * @param s A string na qual a substituição será feita.
 * @param num O número binário para substituição.
 * @return A string resultante após a substituição.
 */
std::string change_letter_by_num(std::string s, char num);

/**
 * @brief Função que resume duas strings com base em uma lógica dos quantificadores.
 * @param s1 O filho esquerdo de um vértice.
 * @param s2 O filho direito de um vértice.
 * @return A string resultante após a aplicação da lógica.
 */
std::string resume_string(std::string s1, std::string s2);

#endif


