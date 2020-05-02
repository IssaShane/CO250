#include "simplex.h"

using namespace std;



vector<Fraction> aux(vector<vector<Fraction>> constraints, vector<Fraction> b) {
  vector<vector <Fraction> > new_constraints;
  for (unsigned int i = 0; i < constraints.size(); i++) {
    vector<Fraction> row;
    for (unsigned int j = 0; j < constraints[0].size(); j++) {
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
  for (unsigned int i = 0; i < constraints[0].size(); i++) {
    x.push_back(Fraction(0,1));
  }
  for (unsigned int i = 0; i < b.size(); i++) {
    x.push_back(b[i]);
  }

  return x;
}

// NOTE: canonical_form assumes that the indices of basis begin at 0 (i.e. the
//   first column of constraints is column 0)
bool canonical_form(const LP &lp) {
  // Check A(B) == I
  for (unsigned int i = 0; i < lp.basis.size(); i++) {
    if (lp.A[i][lp.basis[i]] != Fraction(1,1)) {return false;}
    //cout << "checked for 1" << endl;
    for (unsigned int j = 0; j < lp.A.size(); j++) {
      //cout << "iterating through column" << endl;
      if (j != i && lp.A[j][lp.basis[i]] != Fraction(0,1)) {return false;}
    }
  }
  //cout << "Checked Identity" << endl;
  // Check C(B) == 0
  for (unsigned int i = 0; i < lp.basis.size(); i++) {
    
    if (lp.obj[lp.basis[i]] != Fraction(0,1)) {
      return false;
    }
  }

  return true;
}

vector<Fraction> subset(const vector<Fraction> &obj, const vector<int> &basis) {
  vector<Fraction> retval;
  for (unsigned int i = 0; i < basis.size(); i++) {
    retval.emplace_back(obj[basis[i]]);
  }
  return retval;
}

void canonicalize(LP &lp) {
  //cout << "canonicalize" << endl;
  matrix old_A = lp.A;
  vector<Fraction> old_b = lp.b;
  // Phase 1: A(b)^(-1)*A

  // find A(b)^(-1)
  matrix Ab = subset(lp.A,lp.basis);
  //cout << "Ab: " << endl << Ab << endl;
  matrix Ab_ = inverse(Ab);
  //cout << "Ab_: " << endl << Ab_ << endl;
  lp.A = Ab_*lp.A;
  //cout << "new A: " << endl << lp.A << endl;
  lp.b = multiply(Ab_,lp.b);
  //cout << "multiplied soln set" << endl;

  // Phase 2: find y : yAx=yb
  vector<Fraction> Zc = subset(lp.obj,lp.basis);
  //cout << "found Zc"<< endl;
  vector<Fraction> y = LU_Solve(transpose(Ab),Zc);
  //cout << "y: " << y << endl;
  lp.obj_const = inner_product(y,old_b);
  //cout << "obj diff: " << multiply(transpose(old_A),y) << endl;
  lp.obj = lp.obj - multiply(transpose(old_A),y);
  //cout << "added obj function" << endl;
  LP_simplify(lp);
}

std::istream & operator>>(std::istream& in, LP& l) {
  char c;
  in >> l.A;
  while (in >> c) if (c == '[') break;
  in >> l.b;
  while (in >> c) if (c == ']') break;
  while (in >> c) if (c == '[') break;
  in >> l.obj;
  while (in >> c) if (c == ']') break;
  in >> l.obj_const;
  while (in >> c) if (c == '[') break;
  in >> l.basis;
  while (in >> c) if (c == ']') break;
  return in;
}

std::ostream & operator<<(std::ostream &out, const LP &l) {
  out << "A[" << l.A.size() << "x" << l.A[0].size() << "]: " << endl << l.A << endl;
  out << "b: " << l.b << endl << "obj: " << l.obj << " + " << l.obj_const << endl;
  out << "basis: " << l.basis << endl;
  return out;
}

void LP_simplify(LP &lp) {
  matrix_simplify(lp.A);
  vec_simplify(lp.obj);
  lp.obj_const.simplify();
  vec_simplify(lp.b);
}
