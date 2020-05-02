#include "matrix_tools.h"

using namespace std;

// Identity(n) returns the nxn identity matrix
// requires: none
// effects: none
// efficiency: O(n²)
matrix Identity(int n) {
  matrix I;
  for (int i = 0; i < n; i++) {
    vector<Fraction> row;
    for (int j = 0; j < n; j++) row.emplace_back(Fraction(0));
    I.emplace_back(row);
  }
  for (int i = 0; i < n; i++) {
    I[i][i] = Fraction(1);
  }
  return I;
}

// matrix_equal(m1, m2) returns true if m1 == m2, and false if otherwise
// requires: m1 and m2 are of equal dimensions
// effects: none
// efficiency: O(n^2)
bool matrix_equal(vector<vector<Fraction>> &m1, vector<vector<Fraction>> &m2) {
  if (m1.size() != m2.size()) return false;
  for (unsigned int i = 0; i < m1.size(); i++) {
    if (!vec_equal(m1[i], m2[i])) return false;
  }
  return true;
}


// multiply(matrix, vec) returns the product of matrix and vec in the 
//   orientation matrix*vec
// Requires: matrix[i].size() == vec.size() for each i in [0,matrix.size()]
// Effects: None
// Efficiency: O(n^2)
vector<int> multiply(const vector<vector<int>> &matrix, const vector<int> &vec) {
  vector <int> product;
  for (unsigned int i = 0; i < matrix.size(); i++) {
    product.push_back(inner_product(matrix[i], vec));
  }
  return product;
}

vector<Fraction> multiply(const vector<vector<Fraction>> &matrix, const vector<Fraction> &vec) {
  vector <Fraction> product;
  for (unsigned int i = 0; i < matrix.size(); i++) {
    product.push_back(inner_product(matrix[i], vec));
  }
  //cout << "col size: " << product.size() << endl;
  return product;
}

// multiply(m1, m2) returns the product of m1 and m2 in the orientation m1*m2
// Requires: m1 and m2 are of compatible dimensions
// Effects: None
// Efficiency: O(n^3)
vector<vector<int>> multiply(const vector<vector<int>> &m1, const vector<vector<int>> &m2) {
  vector<vector<int>> product;
  for (unsigned int i = 0; i < m1.size(); i++) {
    product.push_back(multiply(m2, m1[i]));
  }
  return product;
}

// multiply(m1, m2) returns the product of m1 and m2 in the orientation m1*m2
// Requires: m1 and m2 are of compatible dimensions
// Effects: None
// Efficiency: O(n^3)
matrix multiply(const matrix &m1, const matrix &m2) {
  //cout << "mult" << endl;
  vector<vector<Fraction>> product;
  for (unsigned int i = 0; i < m2[0].size(); i++) {
    //cout << "col: " << i << endl;
    vector<Fraction> col;
    for (unsigned int j = 0; j < m2.size(); j++) col.push_back(m2[j][i]);
    product.push_back(multiply(m1, col));
  }
  matrix_simplify(product);
  //cout << "non trans product[" << product.size() << "x" << product[0].size() << "]: " << endl << product << endl;
  matrix retval = transpose(product);
  //cout << "retval[" << retval.size() << "x" << retval[0].size() << "]: " << endl << retval << endl;
  return retval;
}

matrix operator*(const matrix &a, const matrix &b) {
  matrix product;
  for (unsigned int i = 0; i < a.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < b[0].size(); j++) {
      Fraction val{0};
      for (unsigned int t = 0; t < a[0].size(); t++) {
        val += (a[i][t]*b[t][j]);
      }
      row.emplace_back(val);
    }
    product.emplace_back(row);
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
  for (unsigned int t = 0; t < m[i].size(); t++) {
    m[j][t] += c*m[i][t];
  }
}

// combine_row(m, i, j, c) adds row i (with coefficient c) to row j
// requires: none
// effects: mutates m
// efficiency: O(n)
void combine_row(vector<vector<Fraction>> &m, int i, int j, Fraction c) {
  for (unsigned int t = 0; t < m[i].size(); t++) {
    m[j][t] += c*m[i][t];
  }
}

// multiply_row(m, i, c) multiplies row i of matrix m by coefficient c
// requires: none
// effects: mutates m
// efficiency: O(n)
void multiply_row(vector<vector<Fraction>> &m, int i, int c) {
  for (unsigned int t = 0; t < m[i].size(); t++) {
    m[i][t] *= c;
  }
}

// inverse(m) returns the value of the inverse of the matrix m
// requires: m.size() == m[i].size for all i in [0,m.size()-1]
// effects: allocates data to be returned
// efficiency: O(n^2)
vector<vector<Fraction>> inverse(vector<vector<Fraction>> &m_) {
  vector<vector<Fraction>> m;
  for (unsigned int i = 0; i < m_.size(); i++) m.push_back(m_[i]);
  
  // build an identity matrix I, to be transformed into the inverse of m
  vector<vector<Fraction>> I;
  for (unsigned int i = 0; i < m.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < m.size(); j++) row.push_back(Fraction(0));
    I.push_back(row);
  }

  for (unsigned int i = 0; i < I.size(); i++) {
    for (unsigned int j = 0; j < I.size(); j++) {
      if (i == j) I[i][j] = Fraction(1);
    }
  }

  for (unsigned int i = 0; i < m.size(); i++) {
    Fraction t = m[i][i];
    for (unsigned int j = i; j < m.size(); j++) m[i][j] /= t;
    for (unsigned int j = 0; j < I.size(); j++) I[i][j] /= t;

    for (unsigned int j = 0; j < m.size(); j++) {
      if (i != j) {
        t = m[j][i];
        for (unsigned int k = 0; k < m.size(); k++) m[j][k] -= (t*m[i][k]);
        for (unsigned int k = 0; k < I.size(); k++) I[j][k] -= (t*I[i][k]);
      }
    }
  }

  matrix_simplify(I);
  return I;
}

matrix inverse_pivot(const matrix &m_) {
  matrix I = Identity((signed)m_.size());
  matrix m;
  for (unsigned int i = 0; i < m_.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < m_[i].size(); j++) {
      row.emplace_back(m_[i][j]);
    }
    m.emplace_back(row);
  }

  for (unsigned int i = 0; i < m.size(); i++) {
    int pivot = 0;
    for (unsigned int j = 0; j < m.size(); j++) {
      if (m[j][i] == Fraction(1)) pivot = j;
    }
    swap_rows(m,i,pivot);
    swap_rows(I,i,pivot);
  }
  return I;
}

// subset(m, basis) returns the matrix subset of m with respect to basis
// requires: basis.size() == size() 
//           basis.size() <= m[i].size() for all i in [0, m.size()-1]
// effects: allocates data to be returned
// efficiency: O(n^2)
vector<vector<Fraction>> subset(vector<vector<Fraction>> &m, vector<int> &basis) {
  vector<vector<Fraction>> sub_m;
  for (unsigned int i = 0; i < m.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < basis.size(); j++) {
      //cout << "(i,j): " << "(" << i << "," << basis[j] << ")" << endl;
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
  for (unsigned int i = 0; i < m.size(); i++) {
    for (unsigned int j = 0; j < m[i].size(); j++) {
      str << m[i][j];
      if (j < m[i].size()-1) str << " ";
      //str << ";";
    }
    if (i < m.size()-1) str << endl;
  }
  return str;
}


// matrix_simplify simplifies the contents of m
// requires: m is a square matrix
// effects: mutates data in m
// efficiency: O(n^2)
void matrix_simplify(vector<vector<Fraction>> &m) {
  for (unsigned int i = 0; i < m.size(); i++) {
    for (unsigned int j = 0; j < m.size(); j++) {
      m[i][j].simplify();
    }
  }
}

// transpose gives the transpose of the given matrix m
// requires: None
// effects: none
// efficiency: O(n^2)
vector<vector<Fraction>> transpose(vector<vector<Fraction>> &m) {
  vector<vector<Fraction>> trans;
  for (unsigned int i = 0; i < m[0].size(); i++) {
    //cout << "row " << i << endl;
    vector<Fraction> row;
    for (unsigned int j = 0; j < m.size(); j++) {
      //cout << "col " << j << endl;
      row.push_back(m[j][i]);
    }
    trans.push_back(row);
  }
  //cout << "end of trans" << endl;
  return trans;
}

// swap_rows(m, i, j) exchanges the values in the ith and jth rows in m
// Requires: 0 <= i, j < m.size()
// Effects: mutates m
// Efficiency: O(n^2)
void swap_rows(matrix &m, int i, int j) {
  for (unsigned int t = 0; t < m[i].size(); t++) {
    Fraction temp = m[i][t];
    m[i][t] = m[j][t];
    m[j][t] = temp;
  }
}

// operator>>(in, m) reads a matrix from standard input and writes its data to m
//   Input is handled in the following format:
// ------------------------------------------------------------------
// [a b c; d e f; g h i] => | a b c |
//                          | d e f |
//                          | g h i |
// ------------------------------------------------------------------
// Effects: mutates m
// Requires: m is empty
istream & operator>>(istream &in, matrix & m) {
  //cout << "matrix i op" << endl;
  char c;
  bool begun = false;
  while (in >> c) {
    if (c == ']') break;
    if (c == '[') begun = true;
    //cout << "c: " << c << endl;
    vector<Fraction> row;
    in >> row;
    
    if (begun) m.emplace_back(row);
    //cout << "top after row: " << in.peek() << endl;
  }
  //cout << "top: " << in.peek() << endl;
  //cout << "exited loop" << endl;
  //cout << "end matrix i op" << endl;
  in.clear();
  return in;
} 
