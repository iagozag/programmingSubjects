#include "../include/utils.h"

#include <string>
using namespace std;

Matrix multiply(Matrix mat1, Matrix mat2) {
    Matrix ans(0, 0, 0, 0); 

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                ans.sumIdx(i, j, mat1.getIdx(i, k) * mat2.getIdx(k, j));

    return ans;
}

long long get_less_sig(long long a){
    string st = to_string(a);
    if(st.size() <= 8) return a;

    string aux = " ";
    for(unsigned i = st.size()-8; i < st.size(); i++) aux += st[i];
    long long res = stol(aux);
    return res;
}
