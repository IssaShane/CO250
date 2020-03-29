#include "linear_systems.h"

Fraction l(const vector<vector<Fraction>> &m, int i, int n) {
  return m[i][n]/m[n][n];
}

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

vector<vector<Fraction>> lower_triangular(const vector<vector<Fraction>> &m) {
  vector<vector<Fraction>> L;
  for (unsigned int i = 0; i < m.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < i; j++) row.push_back(0);
    row.push_back(1);
    for (unsigned int t = i+1; t < m.size(); t++) row.push_back(0);
    L.push_back(row);
  }

  for (unsigned int i = 1; i < m.size(); i++) {
    for (unsigned int j = 0; j < i; j++) {
      L[i][j] = l(m,i,j);
    }
  }

  return L;
}

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

Fraction find_x2(vector<vector<Fraction>> &m, vector<Fraction> &b, Fraction x1) {
  Fraction retval = (b[1] - x1*m[1][0]) / m[1][1];
  retval.simplify();
  return retval;
}

vector<Fraction> forward_sub(vector<vector<Fraction>> &m, vector<Fraction> &b) {
  vector<Fraction> y;
  y.emplace_back(b[0]/m[0][0]);
  for (unsigned int i = 1; i < m.size(); i++) {
    Fraction sum = 0;
    for (unsigned int t = 0; t < i-1; t++) {
      sum += y[t]*m[i][t];
    }
    y.emplace_back((b[i]-sum)/m[i][i]);
  }
  return y;
}

vector<Fraction> backward_sub(vector<vector<Fraction>> &m, vector<Fraction> &b) {
  vector<Fraction> x;
  for (unsigned int i = 0; i < m.size(); i++) x.emplace_back(Fraction(0));
  x[m.size()-1] = b[m.size()-1]/m[m.size()-1][m[0].size()-1];
  for (unsigned int i = m.size()-2; i >= 0; i--) {
    Fraction sum = 0;
    for (unsigned int t = m.size()-1; t >= 0; t--) {
      sum += x[t]*m[i][t];
    }
    x.emplace_back((b[i]-sum)/m[i][i]);
  }
  return x;
}

matrix pivot(const matrix &m) {
  matrix P;
  // form the identity matrix of appropriate size
  for (unsigned int i = 0; i < m.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < i; j++) row.emplace_back(Fraction(0));
    row.emplace_back(Fraction(1));
    for (unsigned int t = i+1; t < m.size(); t++) row.emplace_back(Fraction(0));
    P.emplace_back(row);
  }

  for (unsigned int i = 0; i < m.size(); i++) {
    int max = i;
    for (unsigned int j = i; j < m.size(); j++) {
      if (m[max][i] < m[j][i]) max = j;
    }
    swap_rows(P, i, max);
  }
  return P;
}

vector<Fraction> LU_Solve(const matrix &m, const vector<Fraction> &b) {
  matrix P = pivot(m);
  matrix m_ = multiply(P,m);
  vector<Fraction> b_ = multiply(P,b);
  matrix L = lower_triangular(m);
  matrix U = upper_triangular(m);
  vector<Fraction> y = forward_sub(L,b_);
  vector<Fraction> x = backward_sub(U,y);
  return x;
}