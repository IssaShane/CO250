#ifndef LINEAR_SYSTEMS_H
#define LINEAR_SYSTEMS_H

#include <iostream>
#include <vector>
#include "fraction.h"
#include "matrix_tools.h"

typedef vector<vector<Fraction>> matrix;

// returns the coefficient needed to eliminate the i-th row with the n-th row
Fraction l(const vector<vector<Fraction>> &m, int i, int n);

// one col operation 
void eliminate_col(vector<vector<Fraction>> &m, int i);

// returns the lower triangular matrix of the matrix m
vector<vector<Fraction>> lower_triangular(const vector<vector<Fraction>> &m);

// returns the upper triangular matrix of the matrix m
vector<vector<Fraction>> upper_triangular(const vector<vector<Fraction>> &m);

// finds the value of x2 in a system of the following form:
// ------------------
// a1x1 = b1
// a2x1 + b2x2 = c2
// ------------------
// where a1, b1, a2, and x1 are known
Fraction find_x2(vector<vector<Fraction>> &m, vector<Fraction> &b, Fraction x1);

vector<Fraction> forward_sub(vector<vector<Fraction>> &m, vector<Fraction>& b);
vector<Fraction> backward_sub(vector<vector<Fraction>> &m, vector<Fraction>& b);

matrix pivot(const matrix &m);

vector<Fraction> LU_Solve(const matrix &m, const vector<Fraction> &b);

#endif