#include <vector>
#include "fraction.h"

using namespace std;

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

Fraction abs(Fraction &x) {
  if (x.getNum() >= 0) return x;
  else return (-1)*x;
}

int argmax(vector<vector<Fraction>> &a, int col) {
  int runmax = 0;
  for (int i = 0; i < a.size(); i++) {
    if (abs(a[i][col]) > a[runmax][col]) runmax = i;
  }

  return runmax;
}

vector<vector<Fraction>>& inverse(vector<vector<Fraction>> &m) {
  int h = 0; // pivot for row
  int k = 0; // pivot for column
  int n = m.size();
  // Initialize the Identity Matrix
  vector<vector<Fraction>> I;
  for (int i = 0; i < n; i++) {
    vector<Fraction> row;
    for (int j = 0; j < i; j++) row.push_back(Fraction(0,1));
    row.push_back(Fraction(1,1));
    for (int t = i+1; t < n; t++) row.push_back(Fraction(0,1));
    I.push_back(row);
  }

  while (h <= n && k <= n) {
    int i_max = argmax(m, k);
    if (m[i_max][k].getNum() == 0) k++;
    else {
      //swap rows h and i_max
      vector<Fraction> temp = m[h];
      m[h] = m[i_max];
      m[i_max] = m[h];
      // Examine all rows below the pivot
      for (int i = h; i < n; i++) {
        Fraction f(0,0);
        f = m[i][k] / m[h][k];
        m[i][k] = Fraction(0,1);
        // Examine all remaining elements in current row
        for (int j = k; j < n; j++) {
          m[i][j] = m[i][j] - m[h][j];
        }
      }
      // Increment pivot row and column
      h++;
      k++;
    }
  }
}