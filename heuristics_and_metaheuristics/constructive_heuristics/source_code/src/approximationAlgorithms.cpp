#include "../include/approximationAlgorithms.h"

#include <fstream>
#include <lemon/matching.h>
#include <lemon/full_graph.h>

using namespace lemon;

bool operator<(const Edge x,const Edge o) {
    return x.w<o.w;
}

ll dist2d(long double x1, long double y1, long double x2, long double y2, int type){
    long double xd = x1-x2;
    long double yd = y1-y2;

    if(type == 0) return (ll)(sqrt(xd*xd+yd*yd)+0.5);

    long double rij = sqrt((xd*xd+yd*yd)/10.0);
    ll tij = (ll)(rij+0.5);

    return tij + (tij < rij);
}

void makeMST(vector<multiset<int>> &adj, vector<long double> &x, vector<long double> &y, int& type) {
    int n = x.size();
    vector<bool> sel(n, false);
    vector<Edge> min_e(n);
    min_e[0].w = 0;
    adj.assign(n,{});

    for(int i=0;i<n;i++) {
        int v = -1;
        for(int j=0;j<n;j++) 
            if((not sel[j]) and (v==-1 or min_e[j].w<min_e[v].w)) v = j;

        sel[v] = true;
        if(min_e[v].to!=-1) { 
            adj[v].insert(min_e[v].to);
            adj[min_e[v].to].insert(v);
        }

        for(int to=0;to<n;to++) {
            auto dist = dist2d(x[v],y[v],x[to],y[to], type);
            if(dist<min_e[to].w) min_e[to].w = dist, min_e[to].to = v;
        }
    }
}

void dfsTATT(vector<long double> &x,vector<long double> &y,vector<multiset<int>> &adj,vector<int> &seq,int v, int p) {
    seq.push_back(v);
    for(auto u:adj[v]) {
        if(u==p) continue;
        dfsTATT(x,y,adj,seq,u,v);
    }
}

void TwiceAroundTheTree(vector<long double> &x, vector<long double> &y, int& type) {
    auto begin = std::chrono::high_resolution_clock::now();
    vector<multiset<int>> adj;
    makeMST(adj,x, y, type);

    vector<int> seq;
    dfsTATT(x,y,adj,seq,0,-1);
    ll cost = 0;
    seq.push_back(0);
    for(auto i=0ULL;i<x.size();i++)
        cost+=dist2d(x[seq[i]],y[seq[i]],x[seq[i+1]],y[seq[i+1]], type);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    ofstream f("data/tatt.txt", ofstream::app);
    f << x.size() << ' ' << cost << ' ' << duration.count() << '\n';
    f.close();
    cout << "Cost: " << cost << '\n';
}

void makeMatching(vector<long double> &x, vector<long double> &y, vector<multiset<int>> &adj, int& type) {
    int n = x.size();
    vector<int> odd;
    map<int,int> mapVertex;
    for(int i=0;i<n;i++) 
        if(adj[i].size()&1ULL) odd.push_back(i);

    ll w = LLONG_MIN;
    for(unsigned long long i=0;i<odd.size();i++) 
        for(auto j = i+1;j<odd.size();j++) 
            w = max(w,dist2d(x[odd[i]],y[odd[i]],x[odd[j]],y[odd[j]], type));
    
    FullGraph g(odd.size());
    typedef FullGraph::EdgeMap<ll> WeightMap;
    WeightMap weight(g);

    int i=0,j;
    for(FullGraph::NodeIt u(g); u != INVALID; ++u,i++){
        mapVertex.insert(make_pair(g.id(u),odd[i]));
        j=0;
        for(FullGraph::NodeIt v(g); v != INVALID; ++v,j++) {
            if(j>i) {
                FullGraph::Edge e = g.edge(u, v);
                weight[e] = w-dist2d(x[odd[i]],y[odd[i]],x[odd[j]],y[odd[j]], type);
            }
        }
    }

    MaxWeightedPerfectMatching<FullGraph, WeightMap> matching(g, weight);
    matching.run();

    for (FullGraph::NodeIt u(g); u != INVALID; ++u) {
        FullGraph::Node v = matching.mate(u);
        if (v != INVALID && g.id(u) < g.id(v)) {  // Print each edge once
            adj[mapVertex[g.id(u)]].insert(mapVertex[g.id(v)]);
            adj[mapVertex[g.id(v)]].insert(mapVertex[g.id(u)]);
        }
    }
}

void dfsHamCyc(vector<multiset<int>> &adj, int v, list<int> &path,int init,int ant) {
    if(ant!=-1) path.push_back(ant);
    if(ant!=-1 and v==init) return;
    int next = *adj[v].begin();
    adj[v].erase(adj[v].begin());
    adj[next].erase(adj[next].lower_bound(v));
    dfsHamCyc(adj,next,path,init,v);
}

void makeHamiltonianCycle(vector<multiset<int>> &adj,list<int> &p) {
    int n = adj.size();
    dfsHamCyc(adj,0,p,0);

    for(auto it = p.begin();it!=p.end();it++) {
        if(adj[*it].size()) {
            list<int> p2;
            dfsHamCyc(adj,*it,p2,*it);
            p2.push_front(*it);
            auto i2 = next(it);
            for(auto i :p2) p.insert(i2,i);
        }
    }
    
    vector<bool> oc(n,false);
    for(auto it = p.begin();it!=p.end();) {
        if(oc[*it]) it = p.erase(it);
        else {
            oc[*it] = true;
            it++;
        }
    }
    p.push_back(0);
}

void Christofides(vector<long double> &x, vector<long double> &y, int& type) {
    auto begin = chrono::high_resolution_clock::now();

    vector<multiset<int>> adj;

    makeMST(adj,x,y, type);
    makeMatching(x,y,adj, type);
    
    list<int> p;
    makeHamiltonianCycle(adj,p);

    ll cost=0;
    for(auto it = next(p.begin());it!=p.end();it++) 
        cost += dist2d(x[*it],y[*it],x[*prev(it)],y[*prev(it)], type);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    ofstream f("data/christofides.txt", ofstream::app);
    f << x.size() << ' ' << cost << ' ' << duration.count() << '\n';
    f.close();
    cout << "Cost: " << cost << '\n';
}