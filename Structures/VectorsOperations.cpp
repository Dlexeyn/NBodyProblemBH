#include "VectorsOperations.hpp"

double operator *(const vector<double> &v1, const vector<double> &v2){
    double res = 0;
    for (size_t i = 0; i < v1.size(); i++){
        res += v1[i] * v2[i];
    }
    return res;
}

vector<double> operator *(const double d, const vector<double> &v1){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] * d;
    }
    return res;
}

vector<double> operator *(const vector<double> &v1, const double d){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] * d;
    }
    return res;
}

vector<double> operator /(const vector<double> &v1, const double d){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] / d;
    }
    return res;
}

vector<double> operator -(const vector<double> &v1, const vector<double> &v2){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] - v2[i];
    }
    return res;
}

vector<double> operator +(const vector<double> &v1, const vector<double> &v2){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] + v2[i];
    }
    return res;
}
