#include "matrix_tools.h"

using namespace std;

// Identity(n) returns the nxn identity matrix
// requires: n >= 1
// effects: creates data
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

// empty(n) returns an nxn matrix filled entirely with zeros
// requires: n >= 1
// effects: creates data
// efficiency: O(n²)
matrix empty(int n) {
  matrix m;
  for (int i = 0; i < n; i++) {
    vector<Fraction> row;
    for (int j = 0; j < n; j++) {
      row.emplace_back(Fraction{0});
    }
    m.emplace_back(row);
  }
  return m;
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

// multiply(matrix, vec) returns the product of matrix and vec
// requires: dim(matrix) == dim(vec)
// effects: creates data
// efficiency: O(n²)
vector<Fraction> multiply(const vector<vector<Fraction>> &matrix, const vector<Fraction> &vec) {
  vector <Fraction> product;
  for (unsigned int i = 0; i < matrix.size(); i++) {
    product.push_back(inner_product(matrix[i], vec));
  }
  return product;
}

// multiply(m1, m2) returns the product of m1 and m2 in the orientation m1*m2
// Requires: m1 and m2 are of compatible dimensions
// Effects: creates data
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

// operator*(a,b) returns the result of multiply(a,b)
matrix operator*(const matrix &a, const matrix &b) {
  matrix product;
  for (unsigned int i = 0; i < a.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < b[0].size(); j++) {
      Fraction val{0};
      for (unsigned int t = 0; t < a[0].size(); t++) {
        val.simplify();
        val += (a[i][t]*b[t][j]);
        val.simplify();
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

// add_column(m, col) adds the column col onto the end of the matrix m
// requires: col.size() == m.size()
// effects: mutates m
// efficiency: O(n)
void add_column(matrix &m, const vector<Fraction> &col) {
  for (unsigned int i = 0; i < m.size(); i++) {
    m[i].emplace_back(col[i]);
  }
}

// inverse(m) returns the value of the inverse of the matrix m
// requires: m.size() == m[i].size for all i in [0,m.size()-1]
// effects: allocates data to be returned
// efficiency: O(n^2)
matrix inverse(const matrix &m_) {
  matrix mat = Identity(m_.size());
  matrix m = m_;
  unsigned int N = m.size();
  while (true) {
  for (unsigned column = 0; column < N; ++column) { 
    // Swap row in case our pivot point is not working
    if (m[column][column] == 0) { 
      unsigned big = column; 
      for (unsigned row = 0; row < N; ++row) 
          if (abs(m[row][column]) > abs(m[big][column])) big = row; 
      // Print this is a singular matrix, return identity ?
      if (big == column) fprintf(stderr, "Singular matrix\n"); 
      // Swap rows                        
      swap_rows(m,column,big);
      swap_rows(mat,column,big);
    } 
    // Set each row in the column to 0  
    for (unsigned row = 0; row < N; ++row) { 
      if (row != column) { 
        Fraction coeff = m[row][column] / m[column][column]; 
        coeff.simplify();
        if (coeff != 0) { 
          for (unsigned j = 0; j < N; ++j) { 
            m[row][j] -= coeff * m[column][j]; 
            mat[row][j] -= coeff * mat[column][j]; 
          } 
          // Set the element to 0 for safety
          m[row][column] = 0; 
        } 
      }
        
    } 
    matrix_simplify(mat);
    matrix_simplify(m);
  } 
  // Set each element of the diagonal to 1
  for (unsigned row = 0; row < N; ++row) { 
    mat[row] = mat[row] / m[row][row];
    m[row] = m[row]/m[row][row];
  }
  matrix_simplify(mat);
  matrix_simplify(m);

  matrix I = Identity(m.size()); 
  if (matrix_equal(I,m)) break;
  }

  matrix_simplify(mat);
  return mat;
}

// inverse_pivot(m) gives the matrix m_ where for nxn matrices A, A_ : mA=A_, 
//   m_A_ = A; that is to say, for a pivot matrix m, inverse_pivot(m) gives the
//   inverse of that pivot matrix
// effects: creates data
// requires: m is an nxn pivot matrix
// efficiency: O(n²)
matrix inverse_pivot(const matrix &m) {
  matrix P = Identity((signed) m.size());
  for (unsigned int i = 0; i < m.size(); i++) {
    int max = i;
    for (unsigned int j = i; j < m.size(); j++) {
      if (abs(m[max][i]) < abs(m[j][i])) max = j;
    }
    swap_rows(P, i, max);
  }
  return P;
}

// subset(m, basis) returns the matrix subset of m with respect to basis
// requires: basis.size() == size() 
//           basis.size() <= m[i].size() for all i in [0, m.size()-1]
// effects: allocates data to be returned
// efficiency: O(n^2)
matrix subset(const matrix &m, const vector<int> &basis) {
  //cout << "m[" << m.size() << "x" << m[0].size() << "]" << endl;
  //cout << "basis: " << basis << endl;
  vector<vector<Fraction>> sub_m;
  for (unsigned int i = 0; i < m.size(); i++) {
    vector<Fraction> row;
    //cout << "row " << i << endl;
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
  char c;
  bool begun = false;
  while (in >> c) {
    if (c == ']') break;
    if (c == '[') begun = true;
    vector<Fraction> row;
    in >> row;
    
    if (begun) m.emplace_back(row);
  }
  in.clear();
  return in;
} 
