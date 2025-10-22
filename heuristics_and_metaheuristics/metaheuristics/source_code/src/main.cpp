#include <fstream>
#include <iostream>
#include "../include/brkga.h"

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

void get_input(string filename,vector<long double> &x, vector<long double> &y, int& type){
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << endl;
        return;
    }

    string word, tp; int n;
    while(file >> word){
        if(word == "DIMENSION") file >> n;
        else if(word == "EDGE_WEIGHT_TYPE") file >> tp;
        else if(word == "NODE_COORD_SECTION") break;
    }

    x.resize(n), y.resize(n);
    type = (tp == "EUC_2D" ? 0 : 1);

    int j;
    for(int i = 0; i < n; i++) file >> j >> x[j-1] >> y[j-1];
    file >> word;

    file.close();
}

int32_t main(int32_t argc, char* argv[]){
	if (argc != 2) {
		cout << "How to use: ./main <file>" << endl;
		exit(0);
	}

    int type;
    vector<long double> x,y;
    string filename = "examples/"; filename += argv[1];
    get_input(filename,x,y, type);

    BRKGA brkga(x.size(), type, x, y);

    ofstream f("data/brkga.txt",ofstream::app);
    f << filename.substr(9) << ' ';
    f.close();
    brkga.run();

    exit(0);
}
