
#include "Matrix.h"

Matrix Matrix::Transposition()
{
    Matrix new_matrix = Matrix(sizeM, sizeN);
    for (int i = 0; i < sizeN; ++i) {
        for (int j = i; j < sizeM; ++j) {
            new_matrix.setMatrixElement(i, j, matrix[j][i]);
            new_matrix.setMatrixElement(j, i, matrix[i][j]);
        }
    }
    return new_matrix;
}

Matrix& Matrix::operator=(const Matrix& M)
{
    matrix.clear();
    this->sizeM = M.Get_sizeM();
    this->sizeN = M.Get_sizeN();

    matrix.resize(sizeN);
    for (auto& line : matrix) {
        line.resize(sizeM);
        fill(line.begin(), line.end(), 0);
    }

    for (int i = 0; i < sizeN; ++i) {
        for (int j = 0; j < sizeM; ++j) {
            matrix[i][j] = M.Get_Matrix()[i][j];
        }
    }

    return *this;
}

void Matrix::setMatrix(const vector<vector<double>>& matrix)
{
    Matrix::matrix = matrix;
}

void Matrix::setElement(int y, int x, double value)
{
    matrix[y][x] = value;
}

Matrix::Matrix(int sizeN, int sizeM)
{
    this->sizeM = sizeM;
    this->sizeN = sizeN;

    matrix.resize(sizeN);
    for (auto& line : matrix) {
        line.resize(sizeM);
        fill(line.begin(), line.end(), 0);
    }
}

Matrix::Matrix(const Matrix &copy)
{
    this->sizeM = copy.Get_sizeM();
    this->sizeN = copy.Get_sizeN();

    matrix.resize(sizeN);
    for (auto& line : matrix) {
        line.resize(sizeM);
        fill(line.begin(), line.end(), 0);
    }

    for (int i = 0; i < sizeN; ++i) {
        for (int j = 0; j < sizeM; ++j) {
            matrix[i][j] = copy.Get_Matrix()[i][j];
        }
    }

}
Matrix Matrix::Cholesky_decomposition(const Matrix &A)
{
    Matrix L(A.Get_sizeN(), A.Get_sizeM());
    if (L.sizeN != L.sizeM) {
        cout << "Error: Cholesky_decomposition\n";
        return L;
    }
    for (int i = 0; i < A.sizeN; i++) {
        for (int j = 0; j <= i; j++) {
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

void Matrix::setMatrixElement(int y, int x, double value)
{
    matrix[y][x] = value;
}
