#ifndef PAIR_HPP
#define PAIR_HPP

/**
 * @brief Estrutura Pair representa um par de valores inteiros.
 */
struct Pair {
    int vert; /**< O primeiro valor inteiro. */
    int color; /**< O segundo valor inteiro (cor). */

    /**
     * @brief Sobrecarga do operador < para comparação.
     * @param p O objeto Pair a ser comparado.
     * @return True se este Pair for menor que p, False caso contrário.
     */
    bool operator<(const Pair &p) const {
        if (color != p.color)
            return color < p.color;
        
        return vert < p.vert;
    }

    /**
     * @brief Sobrecarga do operador > para comparação.
     * @param p O objeto Pair a ser comparado.
     * @return True se este Pair for maior que p, False caso contrário.
     */
    bool operator>(const Pair &p) const {
        if (color != p.color)
            return color > p.color;
        
        return vert > p.vert;
    }

    /**
     * @brief Sobrecarga do operador >= para comparação.
     * @param p O objeto Pair a ser comparado.
     * @return True se este Pair for maior ou igual a p, False caso contrário.
     */
    bool operator>=(const Pair &p) const {
        return !(p < *this);
    }
};

#endif

