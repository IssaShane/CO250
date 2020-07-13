#include "linear_systems.h"

// l(m,i,n) gives the coefficient c : c*m(i,n) == m(n,n)
// requires: 0 <= i,n <= dim(m)
//           m is an nxn matrix
// effects: creates data
// efficiency: O(1)
Fraction l(const vector<vector<Fraction>> &m, int i, int n) {
  return m[i][n]/m[n][n];
}

// eliminate_col(m,n) performs all required matrix row operations to set all
//   values in the row n below the diagonal to zero
// effects: mutates m
// requires: 0 <= dim(m) <= n
// efficiency: O(n²)
void eliminate_col(vector<vector<Fraction>> &m, int n) {
  for (unsigned int j = n+1; j < m.size(); j++) {
    if(m[n][n] != Fraction(0)) combine_row(m, n, j, (-1)*l(m,j,n));
    else {
      for (unsigned int t = 0; t < m.size(); t++) {
        if (m[t][t] != Fraction(0)) {
          vector<Fraction> temp = m[t];
          m[t] = m[n];
          m[n] = m[t];
          combine_row(m, n, j, (-1)*l(m,j,n));
        }
      }
    }
  }
}

// lower_triangular(m) gives the lower triangular matrix L : LU = m for an 
//   upper triangular matrix U, and an nxn matrix m
// requries: m is an nxn matrix
// effects: creates data
// efficiency: O(n²)
vector<vector<Fraction>> lower_triangular(const vector<vector<Fraction>> &m) {
  vector<vector<Fraction>> L = Identity((signed)m.size());

  for (unsigned int i = 1; i < m.size(); i++) {
    for (unsigned int j = 0; j < i; j++) {
      L[i][j] = l(m,i,j);
    }
  }

  return L;
}

// upper_triangular(m) gives the upper triangular matrix U : LU = m for a
//   lower triangular matrix L, and an nxn matrix m
// requires: m is an nxn matrix
// effects: creates data
// efficiency: O(n²)
vector<vector<Fraction>> upper_triangular(const vector<vector<Fraction>> &m) {
  vector<vector<Fraction>> m1 = m;
  for (unsigned int i = 0; i < m1[0].size()-1; i++) eliminate_col(m1, i); 
  
  for (unsigned int i = 0; i < m1.size(); i++) {
    for (unsigned int j = 0; j < m1[i].size(); j++) {
      m1[i][j].simplify();
    }
  }
  return m1;
}

// LU_decomp(m) gives a vector (L,U) where L is a lower triangular matrix and U
//   is an upper triangular matrix : LU = m
// requires: m must be an nxn matrix with an appropriate pivot matrix I
// effects: creates data
// efficiency: O(n²)
vector<matrix> LU_decomp(const matrix &m) {
  matrix L = Identity((signed) m.size());
  matrix U = m;

  for (unsigned int i = 0; i < m.size(); i++) {
    for (unsigned int j = i+1; j < m.size(); j++) {
      L[j][i] = l(U,j,i);
    }
    eliminate_col(U,i);
  }
  matrix_simplify(L);
  matrix_simplify(U);
  vector<matrix> retval;
  retval.emplace_back(L);
  retval.emplace_back(U);
  return retval;
}

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
  matrix P = pivot(m);
  matrix m_ = multiply(P,m);
  vector<Fraction> b_ = multiply(P,b);
  vector<matrix> LU = LU_decomp(m_);
  matrix L = LU[0];
  matrix U = LU[1];
  vector<Fraction> y = forward_sub(L,b_);
  vector<Fraction> x = backward_sub(U,y);
  
  return x;
}