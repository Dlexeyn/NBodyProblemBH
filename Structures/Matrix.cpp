
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

void Matrix::setElement(int y, int x, double value)
{
    matrix[y][x] = value;
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
Matrix Matrix::Cholesky_decomposition(Matrix A)
{
    Matrix L(A.sizeN, A.sizeM);
    if (L.sizeN != L.sizeM)
    {
        cout << "Error: Cholesky_decomposition\n";
        return L;
    }
    for (int i = 0; i < A.sizeN; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            double sum = 0;
            for (int k = 0; k < j; k++)
                sum += L.matrix[i][k] * L.matrix[j][k];

            if (i == j)
                L.matrix[i][j] = sqrt(A.matrix[i][i] - sum);
            else
                L.matrix[i][j] = (1.0 / L.matrix[j][j] * (A.matrix[i][j] - sum));
        }
    }
    return L;
}
