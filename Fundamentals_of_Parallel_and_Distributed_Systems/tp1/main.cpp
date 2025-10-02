#include <iostream>
#include <vector>
#include <pthread.h>
#include "passa_tempo.h"

using namespace std;

struct thread{
	int id, group, start, m;
	vector<pair<int, int>> pos;

	thread() {}
	thread(int _id, int _group, int _start, int _m): id(_id), group(_group), start(_start), m(_m){
		for(int i = 0; i < m; i++){
			int p, time; cin >> p >> time;
			pos.emplace_back(p, time);
		}
	}
};

vector<thread> t;

int main(){
	int N, T; cin >> N >> T;
	
	pthread_t threads[T];
	for(int i = 0; i < T; i++){
		int id, gp, start, m; cin >> id >> gp >> start >> m;
		t.emplace_back(id, gp, start, m);
	}

	cout << 1 << endl;

	exit(0);
}
