#ifndef PAIR_HPP
#define PAIR_HPP

struct Pair{
    int vert;
    int color;

    bool operator<(const Pair &p) const {
        if (color != p.color)
            return color < p.color;
        
        return vert < p.vert;
    }

    bool operator>(const Pair &p) const {
        if (color != p.color)
            return color > p.color;
        
        return vert > p.vert;
    }

    bool operator>=(const Pair &p) const {
        return !(p < *this);
    }
};

#endif 
