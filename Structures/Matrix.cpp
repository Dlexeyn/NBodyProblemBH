
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
Matrix Matrix::Cholesky_decomposition(Matrix A)
{
    Matrix L(A.sizeN, A.sizeM);
    if (L.sizeN != L.sizeM)
    {
        std::cout << "Error :: Not square matrix in Cholesky_decomposition!" << std::endl;
        return L;
    }
    for (int i = 0; i < A.sizeN; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            double sum = 0;
            for (int k = 0; k < j; k++)
                sum += L[i][k] * L[j][k];

            if (i == j)
                L[i][j] = std::sqrt(A[i][i] - sum);
            else
                L[i][j] = (1.0 / L[j][j] * (A[i][j] - sum));
        }
    }
    return L;
}