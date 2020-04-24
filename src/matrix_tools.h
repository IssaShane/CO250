#ifndef MATRIX_TOOLS_H
#define MATRIX_TOOLS_H

#include <vector>
#include "fraction.h"

using namespace std;

typedef vector<vector<Fraction>> matrix;

// Vector Operations
void vec_simplify(vector<Fraction>&);

// Matrix/Vector artithmatic
int inner_product(const vector<int>&, const vector<int>&);
Fraction inner_product(const vector<Fraction>&, const vector<Fraction>&);
vector<int> multiply(const vector<vector<int>>&, const vector<int>&);
vector<Fraction> multiply(const vector<vector<Fraction>>&, const vector<Fraction>&);

// Matrix/Matrix arithmetic
vector<vector<Fraction>> multiply(const vector<vector<Fraction>> &m1, const vector<vector<Fraction>> &m2);

// Matrix row operations

// adds row i to row j with coefficient c in matrix m
void combine_row(vector<vector<Fraction>> &m, int i, int j, int c);
void combine_row(vector<vector<Fraction>> &m, int i, int j, Fraction c);
// multiplies all entries of row i by coefficient c
void multiply_row(vector<vector<Fraction>> &m, int i, int c);

bool vec_equal(vector<Fraction> a, vector<Fraction> b);
bool matrix_equal(vector<vector<Fraction>> &m1, vector<vector<Fraction>> &m2);

// Matrix operations
matrix Identity(int);
vector<vector<Fraction>> inverse(vector<vector<Fraction>>&);
matrix inverse_pivot(const matrix&);
vector<vector<Fraction>> subset(vector<vector<Fraction>> &m, vector<int> &basis);
void matrix_simplify(vector<vector<Fraction>> &m);
vector<vector<Fraction>> transpose(vector<vector<Fraction>>&);
void swap_rows(matrix &m, int i, int j);

// Input / Output
istream &operator>>(istream &, matrix&);
ostream &operator<<(ostream &str, const vector<vector<Fraction>> &m);
ostream &operator<<(ostream &str, const vector<Fraction> &v);
istream &operator>>(istream&, vector<Fraction>&);

#endif