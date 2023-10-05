#include "../include/destinationpackages.h"

using namespace std;

DestinationPackages::~DestinationPackages() {}

void DestinationPackages::add_package(Package* g){
    if(_packs.count(g->get_nome()) != 0) 
        _packs.at(g->get_nome()).push_back(g);
    else 
        _packs.insert(pair<string, vector<Package *>>(g->get_nome(), {g}));
}

double DestinationPackages::custo_total(){
    double custo_total = 0;
    for(auto const& pessoa: _packs)
        for(auto pack: pessoa.second)
            custo_total += pack->calculate_cost();

    return custo_total;
}

double DestinationPackages::custo_total(string nome){
    if(_packs.count(nome) == 0) return 0;

    double custo_total = 0;
    for(auto pack: _packs.at(nome))
        custo_total += pack->calculate_cost();

    return custo_total;
}

