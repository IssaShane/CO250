#ifndef LUDECOMP_H
#define LUDECOMP_H

#include "matrix_tools.h"

// returns the coefficient needed to eliminate the i-th row with the n-th row
Fraction l(const vector<vector<Fraction>> &m, int i, int n);

// one col operation 
void eliminate_col(vector<vector<Fraction>> &m, int i);
// returns the lower triangular matrix of the matrix m
vector<vector<Fraction>> lower_triangular(const vector<vector<Fraction>> &m);

// returns the upper triangular matrix of the matrix m
vector<vector<Fraction>> upper_triangular(const vector<vector<Fraction>> &m);

vector<matrix> LU_decomp(const matrix &m);

#endif