#include "ludecomp.h"

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
  vector<matrix> decomp = LU_decomp(m);
  return decomp[0];
}

// upper_triangular(m) gives the upper triangular matrix U : LU = m for a
//   lower triangular matrix L, and an nxn matrix m
// requires: m is an nxn matrix
// effects: creates data
// efficiency: O(n²)
vector<vector<Fraction>> upper_triangular(const vector<vector<Fraction>> &m) {
  vector<matrix> decomp = LU_decomp(m);
  return decomp[1];
}

// LU_decomp(m) gives a vector (L,U) where L is a lower triangular matrix and U
//   is an upper triangular matrix : LU = m
// requires: m must be an nxn matrix with an appropriate pivot matrix I
// effects: creates data
// efficiency: O(n²)
vector<matrix> LU_decomp(const matrix &m) {
  matrix L = Identity((signed) m.size());
  matrix U = m;
  matrix P = Identity((signed) m.size());

  for (unsigned int i = 0; i < m.size(); i++) {
    // check to ensure that U[i][i] is of the max absolute value in the i-th 
    //   column
    int max = i;
    for (unsigned int j = i; j < m.size(); j++) {
      //cout << "max iteration: " << j << endl;
      if (abs(U[max][i]) < abs(U[j][i])) max = j;
    }
    //cout << "found max: " << max << endl;
    swap_rows(U, i, max);
    swap_rows(P, i, max);
    //cout << "U: " << endl << U << endl;

    
    // fill L with the appropriate coefficient
    for (unsigned int j = i+1; j < m.size(); j++) {
      L[j][i] = l(U,j,i);
    }
    
    swap_rows_below_diag(L, i, max);
    matrix_simplify(U);
    // eliminate all entrants in the i-th column below the diagonal
    eliminate_col(U,i);
    matrix_simplify(L);
    matrix_simplify(U);
  }
  
  vector<matrix> retval;
  retval.emplace_back(L);
  retval.emplace_back(U);
  retval.emplace_back(P);
  return retval;
}