#ifndef VECTORSOPERATIONS_HPP
#define VECTORSOPERATIONS_HPP

#include <vector>

using namespace std;

double operator*(const vector<double>& v1, const vector<double>& v2);

vector<double> operator*(const double d, const vector<double>& v1);

vector<double> operator*(const vector<double>& v1, const double d);

vector<double> operator/(const vector<double>& v1, const double d);

vector<double> operator-(const vector<double>& v1, const vector<double>& v2);

vector<double> operator+(const vector<double>& v1, const vector<double>& v2);

#endif // VECTORSOPERATIONS_HPP
