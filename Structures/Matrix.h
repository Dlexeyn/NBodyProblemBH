#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Matrix {
    int sizeN;
    int sizeM;
    vector<vector<long double>> matrix;

public:
    void setMatrix(const vector<vector<long double>>& matrix);

    void setElement(int y, int x, long double value);

    void reset();

    Matrix(int sizeN, int sizeM);

    Matrix(const Matrix &copy);

    vector<vector<long double>> Get_Matrix() const
    {
        return this->matrix;
    }

    int Get_sizeN() const
    {
        return this->sizeN;
    }

    int Get_sizeM() const
    {
        return this->sizeM;
    }

    vector<vector<long double>> Get_matrix()
    {
        return this->matrix;
    }

    Matrix Transposition();

    Matrix& operator=(const Matrix& M);

    friend Matrix operator+(const Matrix& M1, const Matrix& M2)
    {
        if (M2.sizeN == M1.sizeN && M2.sizeM == M1.sizeM) {
            Matrix Result = Matrix(M1.sizeN, M2.sizeM);
            for (int i = 0; i < Result.sizeN; i++)
                for (int j = 0; j < Result.sizeM; j++) {
                    Result.matrix[i][j] = M1.matrix[i][j] + M2.matrix[i][j];
                }
            return Result;
        } else
            exit(1);
    }
    Matrix Cholesky_decomposition(const Matrix &A);

    friend Matrix operator*(const long double num, const Matrix& M)
    {
        Matrix Result = M;
        for (int i = 0; i < Result.sizeN; i++)
            for (int j = 0; j < Result.sizeM; j++) {
                Result.matrix[i][j] *= num;
            }
        return Result;
    }

    friend Matrix operator/(const Matrix& M, const long double num)
    {
        Matrix Result = M;
        for (int i = 0; i < Result.sizeN; i++)
            for (int j = 0; j < Result.sizeM; j++) {
                Result.matrix[i][j] /= num;
            }
        return Result;
    }

    friend Matrix operator*(const Matrix& M1, const Matrix& M2)
    {
        if (M1.sizeM == M2.sizeN) {
            Matrix Result = Matrix(M1.sizeN, M2.sizeM);
            for (int i = 0; i < M1.sizeN; i++) {
                for (int j = 0; j < M2.sizeM; j++) {
                    for (int k = 0; k < M1.sizeM; k++) {
                        Result.matrix[i][j] += M1.matrix[i][k] * M2.matrix[k][j];
                    }
                }
            }
            return Result;
        }
        exit(1);
    }
    ~Matrix(){
        matrix.clear();
    }
};

#endif // UNTITLED_MATRIX_H
