#include "../include/utils.h"

#include <string>
using namespace std;

void multiply(long long** mat1, long long** mat2, long long** seg) {
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            seg[i][j] = 0;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                seg[i][j] += mat1[i][k] * mat2[k][j];
}

long long get_less_sig(long long a){
    string st = to_string(a);
    if(st.size() <= 8) return a;

    string aux = " ";
    for(unsigned i = st.size()-8; i < st.size(); i++) aux += st[i];
    long long res = stol(aux);
    return res;
}
