#include "linear_systems.h"

Fraction l(vector<vector<Fraction>> &m, int i, int n) {
  //cout << "m[i][n]: " << m[i][n] << " m[n][n]: " << m[n][n] << endl;
  return m[i][n]/m[n][n];
}

void eliminate_col(vector<vector<Fraction>> &m, int n) {
  for (int j = n+1; j < m.size(); j++) {
    //cout << "i: " << j << " n: " << n << endl << "l(i,n): " << l(m,j,n) << endl;
    if(m[n][n] != Fraction(0)) combine_row(m, n, j, (-1)*l(m,j,n));
    else {
      for (int t = 0; t < m.size(); t++) {
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

vector<vector<Fraction>> lower_triangular(vector<vector<Fraction>> &m) {
  vector<vector<Fraction>> L;
  for (int i = 0; i < m.size(); i++) {
    vector<Fraction> row;
    for (int j = 0; j < i; j++) row.push_back(0);
    row.push_back(1);
    for (int t = i; t < m.size(); t++) row.push_back(0);
    L.push_back(row);
  }

  for (int i = 1; i < m.size(); i++) {
    for (int j = 0; j < i; j++) {
      L[i][j] = l(m,i,j);
    }
  }

  return L;
}

vector<vector<Fraction>> upper_triangular(vector<vector<Fraction>> &m) {
  vector<vector<Fraction>> m1 = m;
  for (int i = 0; i < m1[0].size()-1; i++) eliminate_col(m1, i); 
  
  for (int i = 0; i < m1.size(); i++) {
    for (int j = 0; j < m1[i].size(); j++) {
      m1[i][j].simplify();
    }
  }
  return m1;
}

Fraction find_x2(vector<vector<Fraction>> &m, vector<Fraction> &b, Fraction x1) {
  Fraction retval = (b[1] - x1*m[1][0]) / m[1][1];
  retval.simplify();
  return retval;
}