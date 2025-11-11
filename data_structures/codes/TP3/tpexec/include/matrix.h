#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
    private:
        long long m[2][2];
    public:
        Matrix();

        Matrix(long long a, long long b, long long c, long long d);

        void setIdx(int i, int j, long long val);

        void sumIdx(int i, int j, long long val);

        long long getIdx(int i, int j);
};

Matrix multiply(Matrix mat1, Matrix mat2);

#endif
