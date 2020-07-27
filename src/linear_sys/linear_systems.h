#ifndef LINEAR_SYSTEMS_H
#define LINEAR_SYSTEMS_H

#include <iostream>
#include <vector>
#include "../lib_vector/matrix_tools.h"

typedef vector<vector<Fraction>> matrix;





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