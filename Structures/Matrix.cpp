
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

void Matrix::setMatrix(const vector<vector<double>> &matrix) {
    Matrix::matrix = matrix;
}

Matrix::Matrix(int sizeN, int sizeM) {
    this->sizeM = sizeM;
    this->sizeN = sizeN;

    matrix.resize(sizeN);
    for(auto &line : matrix)
    {
        line.resize(sizeM);
        fill(line.begin(), line.end(), 0);
    }
}
