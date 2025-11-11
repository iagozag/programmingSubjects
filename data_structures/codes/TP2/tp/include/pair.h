#ifndef PAIR_HPP
#define PAIR_HPP

// Definição da estrutura Pair
struct Pair{
    int vert;    // Um valor associado a vértice
    int color;   // Um valor associado a cor

    // Operador de comparação menor que
    bool operator<(const Pair &p) const {
        if (color != p.color)
            return color < p.color;
        
        return vert < p.vert;
    }

    // Operador de comparação maior que
    bool operator>(const Pair &p) const {
        if (color != p.color)
            return color > p.color;
        
        return vert > p.vert;
    }

    // Operador de comparação maior ou igual
    bool operator>=(const Pair &p) const {
        return !(p < *this);
    }
};

#endif 

