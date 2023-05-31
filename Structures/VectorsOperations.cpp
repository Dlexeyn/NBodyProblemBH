#include "VectorsOperations.hpp"

long double operator*(const vector<long double>& v1, const vector<long double>& v2)
{
    long double res = 0;
    for (size_t i = 0; i < v1.size(); i++) {
        res += v1[i] * v2[i];
    }
    return res;
}

vector<long double> operator*(const long double d, const vector<long double>& v1)
{
    vector<long double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++) {
        res[i] = v1[i] * d;
    }
    return res;
}

vector<long double> operator*(const vector<long double>& v1, const long double d)
{
    vector<long double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++) {
        res[i] = v1[i] * d;
    }
    return res;
}

vector<long double> operator/(const vector<long double>& v1, const long double d)
{
    vector<long double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++) {
        res[i] = v1[i] / d;
    }
    return res;
}

vector<long double> operator-(const vector<long double>& v1, const vector<long double>& v2)
{
    vector<long double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++) {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

vector<long double> operator+(const vector<long double>& v1, const vector<long double>& v2)
{
    vector<long double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++) {
        res[i] = v1[i] + v2[i];
    }
    return res;
}
