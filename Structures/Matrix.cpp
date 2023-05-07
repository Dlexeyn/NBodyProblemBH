//
// Created by akimfeopentov on 06.05.23.
//

#include "Matrix.h"

void Matrix::Transposition() {
    double t;
    for (int i = 0; i < sizeN; ++i) {
        for (int j = i; j < sizeM; ++j) {
            t = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = t;
        }
    }
}

Matrix Matrix::operator+(const Matrix M1) {
    if (sizeN == M1.sizeN && sizeM == M1.sizeM) {
        for (int i = 0; i < sizeN; i++)
            for(int j = 0; j < sizeM;j++){
                matrix[i][j]+=M1.matrix[i][j];
            }
    }
    else
        exit(1);
    return *this;
}
Matrix Matrix::operator-(const Matrix M1) {
    if (sizeN == M1.sizeN && sizeM == M1.sizeM) {
        for (int i = 0; i < sizeN; i++)
            for(int j = 0; j < sizeM;j++){
                matrix[i][j]-=M1.matrix[i][j];
            }
    }
    else
        exit(1);
    return *this;
}

void Matrix::setMatrix(const vector<vector<double>> &matrix) {
    Matrix::matrix = matrix;
}

Matrix Matrix::operator*(const double c) {
    for (int i = 0; i < sizeN; i++)
        for(int j = 0; j < sizeM;j++){
            matrix[i][j]*=c;
        }
    return *this;
}