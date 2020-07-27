#include "linear_systems.h"




Fraction find_x2(vector<vector<Fraction>> &m, vector<Fraction> &b, Fraction x1) {
  Fraction retval = (b[1] - x1*m[1][0]) / m[1][1];
  retval.simplify();
  return retval;
}

// forward_sub(m,b) solves the system my=b for the vector y, matrix m, and  
//   solution set b, where m is lower triangular
// requires: m is lower triangular
// effects: creates data
// efficiency: O(n)
vector<Fraction> forward_sub(vector<vector<Fraction>> &m, vector<Fraction> &b) {
  
  vector<Fraction> y;
  y.emplace_back(b[0]/m[0][0]);
  for (unsigned int i = 1; i < m.size(); i++) {
    Fraction sum = 0;
    for (unsigned int t = 0; t <= i-1; t++) {
      sum += y[t]*m[i][t];
    }
    y.emplace_back((b[i]-sum)/m[i][i]);
  }
  vec_simplify(y);
  return y;
}

// backward_sub(m,b) solves the system my=b for the vector y, matrix m, and  
//   solution set b, where m is upper triangular
// requires: m is upper triangular
// effects: creates data
// efficiency: O(n)
vector<Fraction> backward_sub(vector<vector<Fraction>> &m, vector<Fraction> &b) {
  vector<Fraction> x;
  for (unsigned int i = 0; i < m.size(); i++) x.emplace_back(0);
  
  
  for (unsigned int i = m.size()-1; (i+1) >= 1; i--) {
    Fraction sum{0};
    for (unsigned int j = i+1; j < m.size(); j++) {
      Fraction product = x[j]*m[i][j];
      product.simplify();
      sum += product;
      sum.simplify();
    }
    
    //cout << "sum: " << sum << endl;
    Fraction diff = b[i] - sum;
    diff.simplify();
    x[i] = (diff/m[i][i]);
    x[i].simplify();
  }
  vec_simplify(x);
  return x;
}

// pivot(m) gives the pivot matrix required to prevent an element along the
//   diagonal of m from being zero during LU decomposition
// requires: m is an nxn matrix
// effects: creates data
// efficiency: O(n²)
matrix pivot(const matrix &m) {
  matrix P = Identity((signed) m.size());
  //cout << "formed the identity matrix: " << P << endl;
  for (unsigned int i = 0; i < m.size(); i++) {
    int max = i;
    for (unsigned int j = i; j < m.size(); j++) {
      //cout << "max iteration: " << j << endl;
      if (abs(m[max][i]) < abs(m[j][i])) max = j;
    }
    //cout << "found max: " << max << endl;
    swap_rows(P, i, max);
    //cout << "end of iteration: " << i << endl;
  }
  return P;
}

// LU_Solve(m,b) returns the solution to the system mx=b via LU decomposition
// requires: m is an invertible nxn matrix
// effects: creates data
// efficiency: O(n²)
vector<Fraction> LU_Solve(const matrix &m, const vector<Fraction> &b) {
  if (matrix_equal(m, Identity((signed)m.size()))) return b;
  vector<matrix> LU = LU_decomp(m);
  matrix L = LU[0];
  matrix U = LU[1];
  matrix P = LU[2];
  vector<Fraction> b_ = multiply(P,b);
  
  vector<Fraction> y = forward_sub(L,b_);
  vector<Fraction> x = backward_sub(U,y);
  return x;
}