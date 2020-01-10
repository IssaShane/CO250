#ifndef MATRIX_TOOLS_H
#define MATRIX_TOOLS_H

#include <vector>
#include "fraction.h"

using namespace std;

// Matrix/Vector artithmatic
int inner_product(vector<int>&, vector<int>&);
Fraction inner_product(vector<Fraction>&, vector<Fraction>&);
vector<int> multiply(vector<vector<int>>&, vector<int>&);
vector<Fraction> multiply(vector<vector<Fraction>>&, vector<Fraction>&);

// Matrix row operations

// adds row i to row j with coefficient c in matrix m
void combine_row(vector<vector<Fraction>> &m, int i, int j, int c);
void combine_row(vector<vector<Fraction>> &m, int i, int j, Fraction c);
// multiplies all entries of row i by coefficient c
void multiply_row(vector<vector<Fraction>> &m, int i, int c);

bool vec_equal(vector<Fraction> a, vector<Fraction> b);
bool matrix_equal(vector<vector<Fraction>> &m1, vector<vector<Fraction>> &m2);

// Matrix operations
vector<vector<Fraction>> inverse(vector<vector<Fraction>>&);
ostream &operator<<(ostream &str, const vector<vector<Fraction>> &m);
ostream &operator<<(ostream &str, const vector<Fraction> &v);
vector<vector<Fraction>> subset(vector<vector<Fraction>> &m, vector<int> &basis);
void matrix_simplify(vector<vector<Fraction>> &m);

#endif