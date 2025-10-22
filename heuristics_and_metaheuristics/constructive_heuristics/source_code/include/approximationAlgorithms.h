#ifndef TATT_H
#define TATT_H

#include <climits>
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

using namespace std;

typedef long long ll;

const ll LINF = 0x3f3f3f3f3f3f3f3fll;

struct Edge {
    ll w=LLONG_MAX;
    int to=-1;
    bool operator<(const Edge &o);
    bool operator<(const Edge o);
};

ll dist2d(long double x1, long double y1, long double x2, long double y2, int type);

void makeMST(vector<multiset<int>> &adj,vector<long double> &x,vector<long double> &y, int& type);
void dfsTATT(vector<long double> &x,vector<long double> &y,vector<multiset<int>> &adj,
           vector<int> &seq,int v, int p);
void TwiceAroundTheTree(vector<long double> &x, vector<long double> &y, int& type);

void dfsHamCyc(vector<multiset<int>> &adj,int v,list<int> &path,int init,int ant=-1);
void Christofides(vector<long double> &x,vector<long double> &y, int& type);
void makeMatching(vector<long double> &x,vector<long double> &y,vector<vector<int>> &adj, int& type);
void makeHamiltonianCycle(vector<multiset<int>> &adj,list<int> &p);

#endif