#ifndef VECTORSOPERATIONS_HPP
#define VECTORSOPERATIONS_HPP

#include <vector>

using namespace std;

long double operator*(const vector<long double>& v1, const vector<long double>& v2);

vector<long double> operator*(const long double d, const vector<long double>& v1);

vector<long double> operator*(const vector<long double>& v1, const long double d);

vector<long double> operator/(const vector<long double>& v1, const long double d);

vector<long double> operator-(const vector<long double>& v1, const vector<long double>& v2);

vector<long double> operator+(const vector<long double>& v1, const vector<long double>& v2);

#endif // VECTORSOPERATIONS_HPP
