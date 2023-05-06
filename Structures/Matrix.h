//
// Created by akimfeopentov on 06.05.23.
//
#include <bits/stdc++.h>
using namespace std;
#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H


class Matrix {
    int sizeN;
    int sizeM;
    vector<vector<double>> matrix;
public:
    void setMatrix(const vector<vector<double>> &matrix);

public:
    Matrix(int sizeN = 0, int sizeM = 0) {
        this->sizeM = sizeM;
        this->sizeN = sizeN;
    }

    int Get_sizeN() {
        return this->sizeN;
    }

    int Get_sizeM() {
        return this->sizeM;
    }

    vector<vector<double>> Get_matrix() {
        return this->matrix;
    }

    void Transposition();
    Matrix operator+(const Matrix M1);
    Matrix operator-(const Matrix M1);
    Matrix operator*(const double c);
    friend Matrix operator * (const Matrix &M1, const Matrix &M2){
        if(M1.sizeM == M2.sizeN){
            Matrix Result = Matrix(M1.sizeN, M2.sizeM);
            vector<vector<double>> res (M1.sizeN, vector<double> (M2.sizeM));
            Result.setMatrix(res);
            for(int i = 0; i < M1.sizeN; i++)
            {
                for(int j = 0; j < M2.sizeM; j++)
                {
                    for(int k = 0; k < M1.sizeM; k++)
                    {
                        Result.matrix[i][j] += M1.matrix[i][k] * M2.matrix[k][j];
                    }
                }
            }
            return Result;
        }

    }

};


#endif //UNTITLED_MATRIX_H
