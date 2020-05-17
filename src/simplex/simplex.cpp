#include "simplex.h"

using namespace std;

LP aux(const LP& lp_) {
  LP aux = lp_;
  matrix I = Identity(aux.A.size());
  for (unsigned int i = 0; i < I.size(); i++) {
    for (unsigned int j = 0; j < I[0].size(); j++) {
      aux.A[i].emplace_back(I[i][j]);
    }
  }

  aux.basis.clear();

  for (unsigned int i = (aux.A[0].size()-aux.b.size()); i < aux.A[0].size(); i++) {
    aux.basis.emplace_back(i);
  }

  for (unsigned int i = 0; i < aux.obj.size(); i++) {
    aux.obj[i] = Fraction{0};
  }
  for (unsigned int i = 0; i < aux.b.size(); i++) {
    aux.obj.emplace_back(Fraction{-1});
  }

  return aux;
}

vector<Fraction> aux_soln(const LP& lp) {
  vector<Fraction> soln;
  //cout << "A.size(): " << lp.A.size() << endl << "b.size(): " <<lp.b.size() << endl;
  for (unsigned int i = 0; i < lp.A[0].size()-lp.b.size(); i++) {
    soln.emplace_back(Fraction{0});
  }
  for (unsigned int i = 0; i < lp.b.size(); i++) {
    soln.emplace_back(lp.b[i]);
  }
  return soln;
}

LP sef(const LP &lp) {
  LP sef = lp;
  for (unsigned int i = 0; i < sef.obj.size(); i++) {
    sef.obj[i]*=(-1);
  }
  return sef;
}

// NOTE: canonical_form assumes that the indices of basis begin at 0 (i.e. the
//   first column of constraints is column 0)
bool canonical_form(const LP &lp) {
  // Check A(B) == I
  for (unsigned int i = 0; i < lp.basis.size(); i++) {
    if (lp.A[i][lp.basis[i]] != Fraction(1,1)) {return false;}
    
    for (unsigned int j = 0; j < lp.A.size(); j++) {
      if (j != i && lp.A[j][lp.basis[i]] != Fraction(0,1)) {return false;}
    }
  }
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
  matrix old_A = lp.A;
  vector<Fraction> old_b = lp.b;
  // Phase 1: A(b)^(-1)*A

  // find A(b)^(-1)
  matrix Ab = subset(lp.A,lp.basis);
  matrix Ab_ = inverse(Ab);
  matrix_simplify(Ab_);
  lp.A = Ab_*lp.A;
  lp.b = multiply(Ab_,lp.b);
  vec_simplify(lp.b);

  // Phase 2: find y : yAx=yb
  vector<Fraction> Zc = subset(lp.obj,lp.basis);
  vector<Fraction> y = LU_Solve(transpose(Ab),Zc);
  vec_simplify(y);
  lp.obj_const += inner_product(y,old_b);
  lp.obj = lp.obj - multiply(transpose(old_A),y);
  vec_simplify(lp.obj);
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
  out << "A[" << l.A.size() << "x" << l.A[0].size() << "]:" << endl << l.A << endl;
  out << "b["<<l.b.size() << "]: " << l.b << endl;
  out << "obj["<<l.obj.size()<<"]: " << l.obj << " + " << l.obj_const << endl;
  out << "basis["<< l.basis.size() << "]: " << l.basis << endl;
  return out;
}

void LP_simplify(LP &lp) {
  matrix_simplify(lp.A);
  vec_simplify(lp.b);
  vec_simplify(lp.obj);
  lp.obj_const.simplify();
  vec_simplify(lp.b);
}

vector<Fraction> simplex_solve(LP &lp) {
  // b[i] >= 0
  for (unsigned int i = 0; i < lp.b.size(); i++) {
    if (lp.b[i] < Fraction{0}) {
      lp.b[i]*=(-1);
      lp.A[i] = (-1)*lp.A[i];
    }
  }
  LP auxil = aux(lp);
  vector<Fraction> soln = aux_soln(auxil);
  LP sef_ = sef(auxil);

  // Phase 1
  vector<Fraction> phase1_soln = phase1(lp);
  vector<Fraction> init_soln;
  for (unsigned int i = 0; i < phase1_soln.size()-lp.b.size(); i++) {
    init_soln.emplace_back(phase1_soln[i]);
  }

  // Phase 2
  vector<Fraction> phase2_soln = phase2(lp,init_soln);
  vector<Fraction> final_soln;
  for (unsigned int i = 0; i < (auxil.obj.size()-auxil.b.size()); i++) {
    final_soln.emplace_back(soln[i]);
  }
  return phase2_soln;
}

vector<Fraction> phase1(LP& lp_) {
  LP lp = aux(lp_);
  vector<Fraction> soln = aux_soln(lp);
  while (true) {
    // check for phase 1 completion
    bool solved = true;
    for (unsigned int i = soln.size()-lp.b.size(); i < soln.size(); i++) {
      if (soln[i] != 0) solved = false;
    }
    if (optimal(lp) && solved) {
      lp_.basis = lp.basis;
      vector<int> cols;
      canonicalize(lp_);
      return soln;
    }

    simplex_iteration(lp, soln);
  }
}

vector<Fraction> phase2(LP& lp, vector<Fraction> &soln) {
  while (true) {
    if (optimal(lp)) {
      return soln;}
    else if (unbounded(lp)) {
      vector<Fraction> newsoln;
      for (unsigned int i = 0; i < soln.size(); i++) 
        newsoln.emplace_back(Fraction{-1});
      return newsoln;
    }
    simplex_iteration(lp, soln);
  }
}

void simplex_iteration(LP &lp, vector<Fraction> &soln) {
  LP_simplify(lp);
  // find k : lp.obj[k] <= 0 && k is not in lp.basis
  unsigned int k = 0;
  bool kchosen = false;
  for (unsigned int i = 0, j = 0; i < lp.obj.size(); i++) {
    if (lp.obj[i] > 0 && i != (unsigned) lp.basis[j]) {
      j++;
      k = i;
      kchosen = true;
      break;
    }
    else if (i == (unsigned) lp.basis[j]) j++;
  }

  if (!kchosen) {
    canonicalize(lp);
    LP_simplify(lp);
    return;
  }

  // TODO: add check for unboundedness
  int m = 0; // leaving value
  Fraction t{INT8_MAX};
  for (unsigned int i = 0; i < lp.A.size(); i++) {
    if (lp.A[i][k] > 0 && Fraction{lp.b[i],lp.A[i][k]} < t) {
      m = lp.basis[i];
      t = Fraction{lp.b[i],lp.A[i][k]};
    }
  }
  
  for (unsigned int i = 0; i < lp.A.size(); i++) {
    soln[lp.basis[i]] = lp.b[i]-(t*lp.A[i][k]);
  }
  
  soln[k] = t;
  // add k to the basis, subtracting m
  vector<int> new_basis;
  for (unsigned int i = 0; i < lp.basis.size(); i++) {
    if (lp.basis[i] != m) {
      new_basis.emplace_back((signed)lp.basis[i]);}
  }
  new_basis.emplace_back((signed)k);
  
  sort (new_basis);
  lp.basis = new_basis;
  LP_simplify(lp);
  canonicalize(lp);
  LP_simplify(lp);
  vec_simplify(soln);
}

bool optimal(const LP& lp) {
  for (unsigned int i = 0, j = 0; i < lp.obj.size(); i++) {
    if (i != (unsigned) lp.basis[j]) {
      if (lp.obj[i] > 0) return false;
      j++;
    }
  }
  return true;
}

bool unbounded(const LP& lp) {
  matrix Ab = subset(lp.A,lp.basis);
  for (unsigned int i =0; i < Ab.size(); i++) {
    for (unsigned int j = 0; j < Ab[0].size(); j++) {
      if (Ab[i][j] > 0) return false;
    }
  }
  return true;
}
