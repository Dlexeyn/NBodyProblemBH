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
    vector<vector<double>> matrix;

public:
    void setMatrix(const vector<vector<double>>& matrix);

    void setElement(int y, int x, double value);

    Matrix(int sizeN, int sizeM);

    int Get_sizeN()
    {
        return this->sizeN;
    }

    int Get_sizeM()
    {
        return this->sizeM;
    }

    vector<vector<double>> Get_matrix()
    {
        return this->matrix;
    }

    void Transposition();

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
    Matrix Cholesky_decomposition(Matrix A);

    friend Matrix operator*(const double num, const Matrix& M)
    {
        Matrix Result = Matrix(M.sizeN, M.sizeM);
        for (int i = 0; i < Result.sizeN; i++)
            for (int j = 0; j < Result.sizeM; j++) {
                Result.matrix[i][j] *= num;
            }
        return Result;
    }

    friend Matrix operator/(const Matrix& M, const double num)
    {
        Matrix Result = Matrix(M.sizeN, M.sizeM);
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
            vector<vector<double>> res(M1.sizeN, vector<double>(M2.sizeM));
            Result.setMatrix(res);
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
};

#endif // UNTITLED_MATRIX_H
