#include "vector_tools.h"

using namespace std;

// vec_simplify(v) simplifies v
void vec_simplify(vector<Fraction> &v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    v[i].simplify();
  }
}

vector<Fraction> operator+(const vector<Fraction> &a, const vector<Fraction> &b) {
  vector<Fraction> retval;
  for (unsigned int i = 0; i < a.size(); i++) {
    retval.emplace_back(a[i] + b[i]);
  }
  return retval;
}

vector<Fraction> operator-(const vector<Fraction> &a, const vector<Fraction> &b) {
  vector<Fraction> retval;
  for (unsigned int i = 0; i < a.size(); i++) {
    retval.emplace_back(a[i] - b[i]);
  }
  return retval;
}

// vec_equal(a,b) returns true if and only if a == b
// requires: a and b are of equal dimension
// effects: none
// efficiency: O(n)
bool vec_equal(vector<Fraction> a, vector<Fraction> b) {
  if (a.size() != b.size()) {
    return false;
  }

  for (unsigned int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

// inner_product(a, b) returns the standard inner product (dot product) 
//   of the vectors a and b
// Requires: a.size() == b.size()
// Effects: None
// Efficiency: O(n)
int inner_product(const vector<int> &a, const vector<int> &b) {
  int product = 0;
  for (unsigned int i = 0; i < a.size(); i++) {
    product += (a[i] * b[i]);
  }
  return product;
}

// inner_product(a, b) returns the standard inner product (dot product) 
//   of the vectors a and b
// Requires: a.size() == b.size()
// Effects: None
// Efficiency: O(n)
Fraction inner_product(const vector<Fraction> &a, const vector<Fraction> &b) {
  Fraction product = Fraction(0);
  if (a.size() != b.size()) return product;
  for (unsigned int i = 0; i < a.size(); i++) {
    product += (a[i] * b[i]);
  }
  return product;
}

// operator*(a, b) returns the standard inner product (dot product) 
//   of the vectors a and b
// Requires: a.size() == b.size()
// Effects: None
// Efficiency: O(n)
Fraction operator*(const vector<Fraction> &a, const vector<Fraction> &b) {
  Fraction product = Fraction(0);
  if (a.size() != b.size()) return product;
  for (unsigned int i = 0; i < a.size(); i++) {
    product += (a[i] * b[i]);
  }
  return product;
}

// operator<<(str, v) outputs the contents of v in a list format to str
// effects: outputs to str
// efficiency: O(n)
ostream &operator<<(ostream &str, const vector<Fraction> &v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    str << v[i];
    if (i < v.size()-1) str << " ";}
  return str;
}

istream & operator>>(istream &in, vector<Fraction> &v) {
  //cout << "vector<Fraction> i op" << endl;
  Fraction i{0};
  while (in >> i) {
    v.emplace_back(i);
  }
  //cout << "top after vec: " << in.peek() << endl;
  in.clear();
  //cout << "end vector<Fraction> i op" << endl;
  return in;
}

istream & operator>>(istream &in, vector<int> &v) {
  //cout << "vec<int> i op" << endl;
  int i;
  while (in >> i) {
    v.emplace_back(i);
  }
  in.clear();
  //cout << "end vector<int> i op" << endl;
  return in;
}

ostream & operator<<(ostream &out, const vector<int> &v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    out << v[i];
    if (i < v.size()-1) out << " ";
  }
  return out;
}