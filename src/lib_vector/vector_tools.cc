#include "vector_tools.h"

using namespace std;

// vec_simplify(v) simplifies every entrant in the vector v
// requires: none
// effects: mutates v
// efficiency: O(n²)
void vec_simplify(vector<Fraction> &v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    v[i].simplify();
  }
}

// contains(v, j) returns true iff j is equal to some entrant of the vector v
// requires: none
// effects: none
// efficiency: O(n)
bool contains(const vector<int> &v, int j) {
  for (unsigned int i = 0; i < v.size(); i++) {
    if (v[i] == j) return true;
  }
  return false;
}

// subset_compliment(basis, vec) gives the vector composed of the entrants 
//   of the vector vec at all indices not existing in the vector basis
// requires: none
// effects: creates data
// efficiency: O(n)
vector<Fraction> subset_compliment(const vector<int> &basis, const vector<Fraction> vec) {
  vector<Fraction> retval;
  for (unsigned int i = 0, j = 0; i < vec.size(); i++) {
    if (i != (unsigned) basis[j]) {
      retval.emplace_back(vec[i]);
    }
    else j++;
  }
  return retval;
}

// operator+(a,b) gives the vector-vector sum of the vectors a and b
// requires: dim(a) == dim(b)
// effects: creates data
// efficiency: O(n)
vector<Fraction> operator+(const vector<Fraction> &a, const vector<Fraction> &b) {
  vector<Fraction> retval;
  for (unsigned int i = 0; i < a.size(); i++) {
    retval.emplace_back(a[i] + b[i]);
  }
  return retval;
}

// operator gives the vector-vector difference of the vectors a and b
// requires: dim(a) == dim(b)
// effects: creates data
// efficiency: O(n)
vector<Fraction> operator-(const vector<Fraction> &a, const vector<Fraction> &b) {
  vector<Fraction> diff;
  for (unsigned int i = 0; i < a.size(); i++) {
    diff.emplace_back(a[i]-b[i]);
  }
  return diff;
}

// operator*(c,v) returns the product of the vector v and the constant c
// requires: none
// effects: creates data
// efficiency: O(n)
vector<Fraction> operator*(const Fraction &c, const vector<Fraction> &v) {
  vector<Fraction> product = v;
  for (unsigned int i = 0; i < v.size(); i++) {
    product[i] *= c;
  }
  return product;
}

// operator/(v,c) returns the product of the vector v and the constant (1/c)
// requires: none
// effects: creates data
// efficiency: O(n)
vector<Fraction> operator/(const vector<Fraction> &v, const Fraction &c) {
  vector<Fraction> product = v;
  for (unsigned int i = 0; i < v.size(); i++) {
    product[i] /= c;
  }
  return product;
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

bool operator==(const std::vector<Fraction> &a, const std::vector<Fraction> &b) {
  return (vec_equal(a,b));
}

bool operator<(const std::vector<Fraction>& a, const std::vector<Fraction> &b) {
  for (unsigned int i = 0; i < a.size(); i++) {
    if (a[i] >= b[i]) return false; 
  }
  return true;
}

bool operator>(const std::vector<Fraction>& a, const std::vector<Fraction> &b) {
  for (unsigned int i = 0; i < a.size(); i++) {
    if (a[i] <= b[i]) return false;
  }
  return true;
}

bool operator<=(const std::vector<Fraction>& a, const std::vector<Fraction> &b) {
  for (unsigned int i = 0; i < a.size(); i++) {
    if (a[i] > b[i]) return false; 
  }
  return true;
}

bool operator>=(const std::vector<Fraction>& a, const std::vector<Fraction> &b) {
  for (unsigned int i = 0; i < a.size(); i++) {
    if (a[i] < b[i]) return false;
  }
  return true;
}

bool operator==(const std::vector<Fraction> &a, const Fraction &b) {
  for (Fraction elem : a) {
    if (elem != b) return false;
  }
  return true;
}

bool operator<(const std::vector<Fraction>& a, const Fraction &b) {
  for (Fraction elem : a) {
    if (elem >= b) return false;
  }
  return true;
}

bool operator>(const std::vector<Fraction>& a, const Fraction &b) {
  for (Fraction elem : a) {
    if (elem <= b) return false;
  }
  return true;
}

bool operator<=(const std::vector<Fraction>& a, const Fraction &b) {
  for (Fraction elem : a) {
    if (elem > b) return false;
  }
  return true;
}

bool operator>=(const std::vector<Fraction>& a, const Fraction &b) {
  for (Fraction elem : a) {
    if (elem < b) return false;
  }
  return true;
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

// operator>>(in,v) takes a group of fractions from the stream in, and stores
//   them in the vector v
// effects: mutates in, v
// efficiency: O(n²)
istream & operator>>(istream &in, vector<Fraction> &v) {
  Fraction i{0};
  while (in >> i) {
    v.emplace_back(i);
  }
  in.clear();
  return in;
}

// operator>>(in,v) takes a group of integers from the stream in, and stores
//   them in the vector v
// effects: mutates in, v
// efficiency: O(n²)
istream & operator>>(istream &in, vector<int> &v) {
  int i;
  while (in >> i) {
    v.emplace_back(i);
  }
  in.clear();
  return in;
}

// operator<<(out, v) outputs all entrants in the vector v to the stream out
// effects: outputs to out
// efficiency: O(n)
ostream & operator<<(ostream &out, const vector<int> &v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    out << v[i];
    if (i < v.size()-1) out << " ";
  }
  return out;
}

// merge(array,l,m,r) carries out the merge step of the merge-sort algorithm
// effects: mutates array
// efficiency: O(n)
void merge(vector<int> &array, int l, int m, int r) {
  int i, j, k, nl, nr;
  //size of left and right sub-arrays
  nl = m-l+1; nr = r-m;
  int larr[nl], rarr[nr];
  //fill left and right sub-arrays
  for(i = 0; i<nl; i++) larr[i] = array[l+i];
  for(j = 0; j<nr; j++) rarr[j] = array[m+1+j];
  i = 0; j = 0; k = l;
  //marge temp arrays to real array
  while(i < nl && j<nr) {
    if(larr[i] <= rarr[j]) {
        array[k] = larr[i];
        i++;
    }else{
        array[k] = rarr[j];
        j++;
    }
    k++;
  }
  while(i<nl) {       //extra element in left array
    array[k] = larr[i];
    i++; k++;
  }
  while(j<nr) {     //extra element in right array
    array[k] = rarr[j];
    j++; k++;
  }
}

// mergeSort(array,l,r) sorts the array according to the merge-sort algorithm
// effects: mutates array, uses recursion
// efficiency: O(nlogn)
void mergeSort(vector<int> &array, int l, int r) {
  if(l < r) {
    int m = l+(r-l)/2;
    // Sort first and second arrays
    mergeSort(array, l, m);
    mergeSort(array, m+1, r);
    merge(array, l, m, r);
  }
}

// sort(array) sorts array by ascending order using the merge-sort algorithm
// effects: mutates array, uses recursion
// efficiency: O(nlogn)
void sort(vector<int> &array) {
  mergeSort(array,0,(signed)array.size()-1);
}