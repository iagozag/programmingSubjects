#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/logged_adaptor.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace boost;
using namespace boost::multiprecision;

#define sz(a) (int)(a.size())

typedef cpp_int ll;

const int MIN_BOUND = 20;
const ll INF = 0x3f3f3f3f3f3f3f3fll;;

ll fexp(ll a, ll b, ll m);

ll legendreSymbol(ll a, ll p);

vector<ll> sieve(const ll& n, ll B);

pair<ll, ll> tonelliShanks(ll n, ll p);

ll gauss(vector<dynamic_bitset<>> a, int n, int m, dynamic_bitset<>& ans);

ll gcd(ll a, ll b);

void quadraticSieve(const ll& n);

#endif // FUNCTIONS_H

