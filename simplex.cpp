#include <vector>
#include <iostream>
#include <assert.h>
#include "fraction.h"

using namespace std;

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

vector<Fraction> aux(vector<vector<Fraction>> constraints, vector<Fraction> b) {
  vector<vector <Fraction> > new_constraints;
  for (int i = 0; i < constraints.size(); i++) {
    vector<Fraction> row;
    for (int j = 0; j < constraints[0].size(); j++) {
      row.push_back(constraints[i][j]);
    }
    new_constraints.push_back(row);
  }

  // get the size of the identity matrix to be appended
  int identity_size = b.size();
  int j = 0;
  for (int i = 0; i < identity_size; i++) {
    for (int k = 0; i < j; k++) {
      new_constraints[k].push_back(Fraction(0,1));
    }
    new_constraints[i].push_back(Fraction(1,1));
    for (int t = j; t < identity_size; t++) {
      new_constraints[t].push_back(Fraction(0,1));
    }
  }

  vector <Fraction> x;
  for (int i = 0; i < constraints[0].size(); i++) {
    x.push_back(Fraction(0,1));
  }
  for (int i = 0; i < b.size(); i++) {
    x.push_back(b[i]);
  }

  return x;
}

// NOTE: canonical_form assumes that the indices of basis begin at 0 (i.e. the
//   first column of constraints is column 0)
bool canonical_form(vector<Fraction> &basis, vector<vector<Fraction>> &constraints, vector<Fraction> &obj) {
  // Check A(B) == I
  for (int i = 0; i < basis.size(); i++) {
    //cout << "iterating through basis" << endl;
    basis[i].simplify();
    //cout << "simplified" << endl;
    int col = basis[i].getNum();
    assert(basis[i].getDenom() == 1);
    if (constraints[i][col] != Fraction(1,1)) {return false;}
    //cout << "checked for 1" << endl;
    for (int j = 0; j < constraints.size(); j++) {
      //cout << "iterating through column" << endl;
      if (j != i && constraints[j][col] != Fraction(0,1)) {return false;}
    }
  }
  //cout << "Checked Identity" << endl;
  // Check C(B) == 0
  for (int i = 0; i < basis.size(); i++) {
    basis[i].simplify();
    int col = basis[i].getNum();
    if (obj[col] != Fraction(0,1)) {
      return false;
    }
  }

  return true;
}

void canonicalize(vector<int> &basis, vector<vector<int>> &constraints, vector<int> &obj, int &obj_const) {
  // TODO: Implement her
}

void test1() {
  cout << "aux:" << endl;
        vector<Fraction> solution;
        solution.push_back(Fraction(0,1));
        solution.push_back(Fraction(0,1));
        solution.push_back(Fraction(6,1));
        solution.push_back(Fraction(7,1));
        vector<vector<Fraction>> arg;
        vector<Fraction> row1;
        row1.push_back(Fraction(1,1));
        row1.push_back(Fraction(2,1));
        vector<Fraction> row2;
        row2.push_back(Fraction(3,1));
        row2.push_back(Fraction(4,1));
        vector<Fraction> row3;
        row3.push_back(Fraction(6,1));
        row3.push_back(Fraction(7,1));
        arg.push_back(row1);
        arg.push_back(row2);

        if (vec_equal(aux(arg, row3), solution)) {
          cout << "success" << endl;
        }
        else {
          cout << "failure" << endl;
        }
}

void test2() {
  cout << "canonical_form:" << endl;
  vector<Fraction> obj;
  obj.push_back(Fraction(2,1));
  obj.push_back(Fraction(3,1));
  obj.push_back(Fraction(0,1));
  obj.push_back(Fraction(0,1));
  obj.push_back(Fraction(0,1));
  vector<vector<Fraction>> constraints;
  vector<Fraction> row1;
  row1.push_back(Fraction(1,1));
  row1.push_back(Fraction(1,1));
  row1.push_back(Fraction(1,1));
  row1.push_back(Fraction(0,1));
  row1.push_back(Fraction(0,1));
  constraints.push_back(row1);
  vector<Fraction> row2;
  row2.push_back(Fraction(2,1));
  row2.push_back(Fraction(1,1));
  row2.push_back(Fraction(0,1));
  row2.push_back(Fraction(1,1));
  row2.push_back(Fraction(0,1));
  constraints.push_back(row2);
  vector<Fraction> row3;
  row3.push_back(Fraction(-1,1));
  row3.push_back(Fraction(1,1));
  row3.push_back(Fraction(0,1));
  row3.push_back(Fraction(0,1));
  row3.push_back(Fraction(1,1));
  constraints.push_back(row3);
  vector<Fraction> basis;
  basis.push_back(Fraction(2,1));
  basis.push_back(Fraction(3,1));
  basis.push_back(Fraction(4,1));
  if (canonical_form(basis, constraints, obj)) {
    cout << "success" << endl;
  }
  else {
    cout << "failure" << endl;
  }
}

void test3() {
  cout << "canonical form:" << endl;
  vector<Fraction> row1;
  row1.push_back(Fraction(1,1));
  row1.push_back(Fraction(1,1));
  row1.push_back(Fraction(0,1));
  vector<Fraction> row2;
  row2.push_back(Fraction(1,1));
  row2.push_back(Fraction(0,1));
  row2.push_back(Fraction(1,1));
  vector<vector<Fraction>> constraints;
  constraints.push_back(row1);
  constraints.push_back(row2);
  vector<Fraction> obj;
  for (int i = 0; i < 3; i++) obj.push_back(Fraction(0,1));
  vector<Fraction> basis;
  basis.push_back(Fraction(0,1));
  basis.push_back(Fraction(1,1));
  //cout << "setup done" << endl;
  if (canonical_form(basis, constraints, obj)) {
    cout << "failure" << endl;
  }
  else {
    cout << "success" << endl;
  }
}

// tests
int main() {
  test1();
  test2();
  test3();

  
  return 0;
}