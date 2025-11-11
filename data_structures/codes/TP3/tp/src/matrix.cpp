#include "../include/matrix.h"
#include "../include/memlog.h"

Matrix::Matrix(){
    m[0][0] = 1, m[0][1] = 0,
    m[1][0] = 0, m[1][1] = 1;

    escreveMemLog((long int)(&(m[0][0])),sizeof(int),0);
    escreveMemLog((long int)(&(m[0][1])),sizeof(int),0);
    escreveMemLog((long int)(&(m[1][0])),sizeof(int),0);
    escreveMemLog((long int)(&(m[1][1])),sizeof(int),0);
}

Matrix::Matrix(long long a, long long b, long long c, long long d){
    m[0][0] = a, m[0][1] = b,
    m[1][0] = c, m[1][1] = d;

    escreveMemLog((long int)(&(m[0][0])),sizeof(int),0);
    escreveMemLog((long int)(&(m[0][1])),sizeof(int),0);
    escreveMemLog((long int)(&(m[1][0])),sizeof(int),0);
    escreveMemLog((long int)(&(m[1][1])),sizeof(int),0);
}

long long* Matrix::operator[](int i){
    return m[i];
}

void Matrix::setIdx(int i, int j, long long val){
    m[i][j] = val;

    escreveMemLog((long int)(&(m[i][j])),sizeof(int),0);
}

void Matrix::sumIdx(int i, int j, long long val){
    int mod = 1e8;
    m[i][j] = (m[i][j] + val) % mod;

    escreveMemLog((long int)(&(m[i][j])),sizeof(int),0);
}

long long Matrix::getIdx(int i, int j){
    leMemLog((long int)(&(m[i][j])),sizeof(int),0);

    return m[i][j];
}

Matrix multiply(Matrix mat1, Matrix mat2) {
    Matrix ans(0, 0, 0, 0); 

    int mod = 1e8;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                ans.sumIdx(i, j, ((mat1.getIdx(i, k)) * mat2.getIdx(k, j)) % mod);

    return ans;
}
