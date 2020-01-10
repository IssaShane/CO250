#include "matrix_tools.h"

using namespace std;

// vec_equal(a,b) returns true if and only if a == b
// requires: a and b are of equal dimension
// effects: none
// efficiency: O(n)
bool vec_equal(vector<Fraction> a, vector<Fraction> b) {
  if (a.size() != b.size()) {
    return false;
  }

  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

// matrix_equal(m1, m2) returns true if m1 == m2, and false if otherwise
// requires: m1 and m2 are of equal dimensions
// effects: none
// efficiency: O(n^2)
bool matrix_equal(vector<vector<Fraction>> &m1, vector<vector<Fraction>> &m2) {
  if (m1.size() != m2.size()) return false;
  for (int i = 0; i < m1.size(); i++) {
    if (!vec_equal(m1[i], m2[i])) return false;
  }
  return true;
}

// inner_product(a, b) returns the standard inner product (dot product) 
//   of the vectors a and b
// Requires: a.size() == b.size()
// Effects: None
// Efficiency: O(n)
int inner_product(vector<int> &a, vector<int> &b) {
  int product = 0;
  for (int i = 0; i < a.size(); i++) {
    product += (a[i] * b[i]);
  }
  return product;
}

// inner_product(a, b) returns the standard inner product (dot product) 
//   of the vectors a and b
// Requires: a.size() == b.size()
// Effects: None
// Efficiency: O(n)
Fraction inner_product(vector<Fraction> &a, vector<Fraction> &b) {
  Fraction product = Fraction(0);
  if (a.size() != b.size()) return product;
  for (int i = 0; i < a.size(); i++) {
    product += (a[i] * b[i]);
  }
  return product;
}

// multiply(matrix, vec) returns the product of matrix and vec in the 
//   orientation matrix*vec
// Requires: matrix[i].size() == vec.size() for each i in [0,matrix.size()]
// Effects: None
// Efficiency: O(n^2)
vector<int> multiply(vector<vector<int>> &matrix, vector<int> &vec) {
  vector <int> product;
  for (int i = 0; i < matrix.size(); i++) {
    product.push_back(inner_product(matrix[i], vec));
  }
  return product;
}

vector<Fraction> multiply(vector<vector<Fraction>> &matrix, vector<Fraction> &vec) {
  vector <Fraction> product;
  for (int i = 0; i < matrix.size(); i++) {
    product.push_back(inner_product(matrix[i], vec));
  }
  return product;
}

// multiply(m1, m2) returns the product of m1 and m2 in the orientation m1*m2
// Requires: m1 and m2 are of compatible dimensions
// Effects: None
// Efficiency: O(n^3)
vector<vector<int>> multiply(vector<vector<int>> &m1, vector<vector<int>> &m2) {
  vector<vector<int>> product;
  for (int i = 0; i < m1.size(); i++) {
    product.push_back(multiply(m2, m1[i]));
  }
  return product;
}

// abs returns the absolute value of x
// requires: none
// effects: none
// efficiency: O(1)
Fraction abs(Fraction &x) {
  if (x.getNum() >= 0) return x;
  else return (-1)*x;
}

// combine_row(m, i, j, c) adds row i (with coefficient c) to row j
// requires: none
// effects: mutates m
// efficiency: O(n)
void combine_row(vector<vector<Fraction>> &m, int i, int j, int c) {
  for (int t = 0; t < m[i].size(); t++) {
    m[j][t] += c*m[i][t];
  }
}

// combine_row(m, i, j, c) adds row i (with coefficient c) to row j
// requires: none
// effects: mutates m
// efficiency: O(n)
void combine_row(vector<vector<Fraction>> &m, int i, int j, Fraction c) {
  for (int t = 0; t < m[i].size(); t++) {
    m[j][t] += c*m[i][t];
  }
}

// multiply_row(m, i, c) multiplies row i of matrix m by coefficient c
// requires: none
// effects: mutates m
// efficiency: O(n)
void multiply_row(vector<vector<Fraction>> &m, int i, int c) {
  for (int t = 0; t < m[i].size(); t++) {
    m[i][t] *= c;
  }
}

// inverse(m) returns the value of the inverse of the matrix m
// requires: m.size() == m[i].size for all i in [0,m.size()-1]
// effects: allocates data to be returned
// efficiency: O(n^2)
vector<vector<Fraction>> inverse(vector<vector<Fraction>> &m_) {
  vector<vector<Fraction>> m;
  for (int i = 0; i < m_.size(); i++) m.push_back(m_[i]);
  
  // build an identity matrix I, to be transformed into the inverse of m
  vector<vector<Fraction>> I;
  for (int i = 0; i < m.size(); i++) {
    vector<Fraction> row;
    for (int j = 0; j < m.size(); j++) row.push_back(Fraction(0));
    I.push_back(row);
  }

  for (int i = 0; i < I.size(); i++) {
    for (int j = 0; j < I.size(); j++) {
      if (i == j) I[i][j] = Fraction(1);
    }
  }

  for (int i = 0; i < m.size(); i++) {
    Fraction t = m[i][i];
    for (int j = i; j < m.size(); j++) m[i][j] /= t;
    for (int j = 0; j < I.size(); j++) I[i][j] /= t;

    for (int j = 0; j < m.size(); j++) {
      if (i != j) {
        t = m[j][i];
        for (int k = 0; k < m.size(); k++) m[j][k] -= (t*m[i][k]);
        for (int k = 0; k < I.size(); k++) I[j][k] -= (t*I[i][k]);
      }
    }
  }

  matrix_simplify(I);
  return I;
}

// subset(m, basis) returns the matrix subset of m with respect to basis
// requires: basis.size() == size() 
//           basis.size() <= m[i].size() for all i in [0, m.size()-1]
// effects: allocates data to be returned
// efficiency: O(n^2)
vector<vector<Fraction>> subset(vector<vector<Fraction>> &m, vector<int> &basis) {
  vector<vector<Fraction>> sub_m;
  for (int i = 0; i < m.size(); i++) {
    vector<Fraction> row;
    for (int j = 0; j < basis.size(); j++) {
      row.push_back(m[i][basis[j]]);
    }
    sub_m.push_back(row);
  }
  return sub_m;
}

// operator<<(str, m) outputs the contents of m in a table format to str
// effects: outputs to str
// efficiency: O(n^2)
ostream &operator<<(ostream &str, const vector<vector<Fraction>> &m) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      str << m[i][j] << " ";
    }
    str << endl;
  }
  return str;
}

// operator<<(str, v) outputs the contents of v in a list format to str
// effects: outputs to str
// efficiency: O(n)
ostream &operator<<(ostream &str, const vector<Fraction> &v) {
  for (int i = 0; i < v.size(); i++) str << v[i] << " ";
  return str;
}

// matrix_simplify simplifies the contents of m
// requires: m is a square matrix
// effects: mutates data in m
// efficiency: O(n^2)
void matrix_simplify(vector<vector<Fraction>> &m) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m.size(); j++) {
      m[i][j].simplify();
    }
  }
}
