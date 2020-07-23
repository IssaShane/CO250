#ifndef MATRIX_TOOLS_H
#define MATRIX_TOOLS_H

#include "vector_tools.h"

using namespace std;

typedef vector<vector<Fraction>> matrix;



// Matrix/Vector artithmatic
vector<int> multiply(const vector<vector<int>>&, const vector<int>&);
vector<Fraction> multiply(const vector<vector<Fraction>>&, const vector<Fraction>&);

// Matrix/Matrix arithmetic
vector<vector<Fraction>> multiply(const vector<vector<Fraction>> &m1, const vector<vector<Fraction>> &m2);
matrix operator*(const matrix&, const matrix&);

// Matrix row operations

// adds row i to row j with coefficient c in matrix m
void combine_row(vector<vector<Fraction>> &m, int i, int j, int c);
void combine_row(vector<vector<Fraction>> &m, int i, int j, Fraction c);
// multiplies all entries of row i by coefficient c
void multiply_row(vector<vector<Fraction>> &m, int i, int c);

// Matrix col operations
void add_column(matrix &m, const vector<Fraction> &col);

bool matrix_equal(vector<vector<Fraction>> &m1, vector<vector<Fraction>> &m2);

// Matrix operations
matrix Identity(int);
Fraction determinant(const matrix&);
vector<vector<Fraction>> inverse(const matrix&);
matrix inverse_pivot(const matrix&);
matrix subset(const matrix &m, const vector<int> &basis);
void matrix_simplify(vector<vector<Fraction>> &m);
vector<vector<Fraction>> transpose(vector<vector<Fraction>>&);
void swap_rows(matrix &m, int i, int j);

// returns the coefficient needed to eliminate the i-th row with the n-th row
Fraction l(const vector<vector<Fraction>> &m, int i, int n);

// one col operation 
void eliminate_col(vector<vector<Fraction>> &m, int i);
// returns the lower triangular matrix of the matrix m
vector<vector<Fraction>> lower_triangular(const vector<vector<Fraction>> &m);

// returns the upper triangular matrix of the matrix m
vector<vector<Fraction>> upper_triangular(const vector<vector<Fraction>> &m);

vector<matrix> LU_decomp(const matrix &m);

// Input / Output
istream &operator>>(istream &, matrix&);
ostream &operator<<(ostream &str, const vector<vector<Fraction>> &m);


#endif