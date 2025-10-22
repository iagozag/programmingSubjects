#include "../include/brkga.h"

#include <fstream>

int dist2d(long double x1, long double y1, long double x2, long double y2, int type){
    long double xd = x1-x2;
    long double yd = y1-y2;

    if(type == 0) return (ll)(sqrt(xd*xd+yd*yd)+0.5);

    long double rij = sqrt((xd*xd+yd*yd)/10.0);
    ll tij = (ll)(rij+0.5);

    return tij + (tij < rij);
}

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

int uniform_int(int l, int r){
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

double uniform_double(double l, double r){
	uniform_real_distribution<double> uid(l, r);
	return uid(rng);
}

int BRKGA::fitness(const vector<double>& keys) {
    vector<int> order(n); iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(), [&](int i, int j){ 
        return keys[i] < keys[j]; 
    });

    int cost = 0;
    for (int i = 0; i < n; i++) cost += dist[order[i]][order[(i+1)%n]];

    return cost;
}

void BRKGA::set_params(){
    pop_size = 200;
    elite_frac = 0.25;
    mutant_frac = 0.1;
    bias = 0.7;
    gens = 100000;
}

void BRKGA::initialize_population(){
    population.resize(pop_size);
    for (auto &p: population){
        p.keys.resize(n);
        for (auto &k : p.keys) k = uniform_double(0, 1);
        p.fitness = fitness(p.keys);
    }
}

void BRKGA::run(){
    auto begin = chrono::high_resolution_clock::now();

    set_params();

    initialize_population();

    int elite_size = int(elite_frac * pop_size);
    int mutant_size = int(mutant_frac * pop_size);
    int offspring_size = pop_size - elite_size - mutant_size;

    for (int g = 0; g < gens; g++) {
        sort(population.begin(), population.end(), [](const Individual& a, const Individual& b){ 
            return a.fitness < b.fitness; 
        });

        vector<Individual> next_pop(population.begin(), population.begin()+elite_size);

        // Offspring (biased crossover)
        for (int i = 0; i < offspring_size; i++) {
            const auto& elite = population[uniform_int(0, elite_size-1)];
            const auto& nonelite = population[uniform_int(elite_size, pop_size - 1)];

            Individual child;
            child.keys.resize(n);
            for (int c = 0; c < n; c++)
                child.keys[c] = (uniform_double(0, 1) < bias) ? elite.keys[c] : nonelite.keys[c];

            child.fitness = fitness(child.keys);
            next_pop.push_back(move(child));
        }

        // Mutants
        for (int i = 0; i < mutant_size; i++) {
            Individual m;
            m.keys.resize(n);
            for (auto &k : m.keys) k = uniform_double(0, 1);
            m.fitness = fitness(m.keys);
            next_pop.push_back(move(m));
        }

        population = move(next_pop);

        // Output progress every few generations
        // if (g % 50 == 0 || g == gens - 1)
        //     cout << "Generation " << g << " | Best cost: " << population[0].fitness << "\n";
    }

    // === Decode and show best solution ===
    const auto& best = population[0];

    vector<int> order(n); iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j){ 
        return best.keys[i] < best.keys[j]; 
    });

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    ofstream f("data/brkga.txt", ofstream::app);
    f << x.size() << ' ' << best.fitness << ' ' << duration.count() << '\n';
    f.close();
}