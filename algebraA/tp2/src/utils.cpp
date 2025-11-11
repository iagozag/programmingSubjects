#include "../include/utils.h"

int num_length(const mc &n, int base){
    return mpz_sizeinbase(n.get_mpz_t(), base);
}

void fexpm(mc &res, const mc &base, const mc &exp, const mc &mod){
    mpz_powm(res.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
}

void fexpm_ui(mc &res, const mc &base, const unsigned long exp, const mc &mod){
    mpz_powm_ui(res.get_mpz_t(), base.get_mpz_t(), exp, mod.get_mpz_t());
}

void fexp(mc &res, const mc &base, const unsigned long exp){
    mpz_pow_ui(res.get_mpz_t(), base.get_mpz_t(), exp);
}

int legendre(const mc &n, const mc &p){
    mc res;
    fexpm(res, n, (p-1)/2, p);
    return res.get_si();
}

int remove_fact(mc &res, mc &a, mc &fact){
    return mpz_remove(res.get_mpz_t(), a.get_mpz_t(), fact.get_mpz_t());
}

void big_sqrt(mc &res, const mc &n){
    mpz_sqrt(res.get_mpz_t(), n.get_mpz_t());
}

void bgcd(mpz_class &res, const mpz_class &a, const mpz_class &b) {
    mpz_gcd(res.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
}

map<mc, int> get_pfactors(mc n, vm base){
    map<mc, int> factors;
    int count = 0;

    if(n < 0) factors[-1] = 1;
    
    for(auto prime : base) if (prime != -1){
        count = remove_fact(n, n, prime);
        if(count > 0) factors[prime] = count, count = 0;
    }

    return factors;
}

Matrix transpose(Matrix &m){
    Matrix nm(sz(m[0]), vm(sz(m)));

    for(int i = 0; i < sz(m[0]); i++) for(int j = 0; j < sz(m); j++)
        nm[i][j] = m[j][i];

    return nm;
}

void tonelliShanks(const mc n, const mc &p, mc& s1, mc &s2){
    mc q, r, z, c, t, t2, b;
    long long s = 0, i, m;

    q = p-1;
    while (q%2 == 0) q /= 2, s++;

    if(s == 1){
        fexpm(s1, n, (p+1)/4, p);
        s2 = p-s1;
        return;
    }

    z = 2;
    while(p-1 != legendre(z, p) and z < p) z++;

    fexpm(c, z, q, p);
    fexpm(r, n, (q+1)/2, p);
    fexpm(t, n, q, p);
    m = s;

    while((t-1)%p != 0) {
        i = 1, t2 = t*t%p;

        for(; i < m; i++) {
            if((t2-1)%p == 0) break;
            t2 = t2*t2%p;
        }

        fexpm_ui(b, c, 1<<(m-i-1), p);

        r = r*b%p;
        c = b*b%p;
        t = t*c%p;
        m = i;
    }

    s1 = r, s2 = p-r;
}
