#include <fstream>
#include <iostream>
#include "../include/approximationAlgorithms.h"

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

int main(int argc, char* argv[]){
	if (argc != 3) {
		cout << "How to use: ./main <file> <algorithm>" << endl;
		exit(0);
	}

    int opt = atoi(argv[2]), type;
    vector<long double> x,y;
    string filename = "examples/"; filename += argv[1];
    get_input(filename,x,y, type);

    switch(opt) {
        case 1:{
            ofstream f("data/tatt.txt",ofstream::app);
            f << filename.substr(9) << ' ';
            f.close();
            TwiceAroundTheTree(x,y, type);
            break;
        }
        case 2: {
            ofstream f("data/christofides.txt",ofstream::app);
            f << filename.substr(9) << ' ';
            f.close();
            Christofides(x,y, type);
            break;
        }
    }

    exit(0);
}
