#include "../include/matrix.h"

Matrix::Matrix(){
    m[0][0] = 1, m[0][1] = 0,
    m[1][0] = 0, m[1][1] = 1;
}

Matrix::Matrix(long long a, long long b, long long c, long long d){
    m[0][0] = a, m[0][1] = b,
    m[1][0] = c, m[1][1] = d;
}

void Matrix::setIdx(int i, int j, long long val){
    m[i][j] = val;
}

void Matrix::sumIdx(int i, int j, long long val){
    int mod = 1e8;
    m[i][j] = (m[i][j] + val) % mod;
}

long long Matrix::getIdx(int i, int j){
    return m[i][j];
}

Matrix multiply(Matrix mat1, Matrix mat2) {
    Matrix ans(0, 0, 0, 0); 

    int mod = 1e8;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                ans.sumIdx(i, j, ((mat1.getIdx(i, k)) % mod) * (mat2.getIdx(k, j) % mod) % mod);

    return ans;
}
