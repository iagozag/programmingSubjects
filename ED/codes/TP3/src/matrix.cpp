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
    m[i][j] += val;
}

long long Matrix::getIdx(int i, int j){
    return m[i][j];
}
