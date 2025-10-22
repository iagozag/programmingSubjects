#ifndef TATT_H
#define TATT_H

#include <list>
#include <chrono>
#include <utility>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <set>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

typedef long long ll;

#define int ll

const int LINF = 0x3f3f3f3f3f3f3f3fll;

int dist2d(long double x1, long double y1, long double x2, long double y2, int type);

int uniform_int(int l, int r);
double uniform_double(double l, double r);

struct BRKGA{
    struct Individual {
        vector<double> keys;
        int fitness;
    };

    int n, type;
    vector<long double> x, y;
    vector<vector<int>> dist;

    int pop_size, gens;
    double elite_frac, mutant_frac, bias;
    vector<Individual> population;
    

    BRKGA(const int& _n, const int& _type, const vector<long double>& _x, const vector<long double>& _y): n(_n), type(_type), x(_x), y(_y) {
        dist = vector<vector<int>>(n, vector<int>(n));
        for (int i = 0; i < n; i++) for(int j = 0; j < n; j++)
            dist[i][j] = dist2d(x[i], y[i], x[j], y[j], type);
    }

    int fitness(const vector<double>& keys);
    void set_params();
    void initialize_population();
    void run();
};

#endif