#ifndef UTILS_H
#define UTILS_H

#include <macros.h>

int num_length(const mc &n, int base);

void fexpm(mc &res, const mc &base, const mc &exp, const mc &mod);

void fexpm_ui(mc &res, const mc &base, const unsigned long exp, const mc &mod);

void fexp(mc &res, const mc &base, const unsigned long exp);

int legendre(const mc &n, const mc &p);

void big_sqrt(mc &res, const mc &n);

void bgcd(mpz_class &res, const mpz_class &a, const mpz_class &b);

int remove_fact(mc &res, mc &a, mc &fact);

map<mc, int> get_pfactors(mc n, vm base);

Matrix transpose(Matrix &m);

void tonelliShanks(const mc n, const mc &p, mc& s1, mc &s2);

#endif // UTILS_H


