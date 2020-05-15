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
  //cout << "aux obj: " << aux.obj << endl;

  

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
  //cout << "A: " << endl << lp.A << endl << "basis: " << lp.basis << endl;
  matrix Ab = subset(lp.A,lp.basis);
  //cout << "Ab: " << endl << Ab << endl;
  matrix Ab_ = inverse(Ab);
  //cout << "Ab_: " << endl << Ab_ << endl;
  matrix_simplify(Ab_);
  //cout << "Ab_: " << endl << Ab_ << endl;
  lp.A = Ab_*lp.A;
  //cout << "new A: " << endl << lp.A << endl;
  lp.b = multiply(Ab_,lp.b);
  vec_simplify(lp.b);
  //cout << "multiplied soln set" << endl;

  // Phase 2: find y : yAx=yb
  vector<Fraction> Zc = subset(lp.obj,lp.basis);
  //cout << "Zc: "<< Zc << endl;
  vector<Fraction> y = LU_Solve(transpose(Ab),Zc);
  vec_simplify(y);
  //cout << "y: " << y << endl;
  lp.obj_const += inner_product(y,old_b);
  //cout << "obj diff: " << multiply(transpose(old_A),y) << endl;
  lp.obj = lp.obj - multiply(transpose(old_A),y);
  vec_simplify(lp.obj);
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
  out << "A[" << l.A.size() << "x" << l.A[0].size() << "]:" << endl << l.A << endl;
  out << "b["<<l.b.size() << "]: " << l.b << endl;
  out << "obj["<<l.obj.size()<<"]: " << l.obj << " + " << l.obj_const << endl;
  out << "basis["<< l.basis.size() << "]: " << l.basis << endl;
  return out;
}

void LP_simplify(LP &lp) {
  matrix_simplify(lp.A);
  //cout << "A after simplify: " << endl << lp.A << endl;
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
  //cout << "simplex solve" << endl;
  LP auxil = aux(lp);
  //cout << "aux LP: " << endl << auxil << endl;
  vector<Fraction> soln = aux_soln(auxil);
  LP sef_ = sef(auxil);
  //cout << "sef LP: " << endl << sef_ << endl;
  //cout << "aux soln: " << soln << endl;

  // Phase 1
  bool auxphase = true;
  canonicalize(auxil);
  while (auxphase) {
    auxphase = false;
    for (unsigned int i = 0; i < auxil.b.size(); i++) {
      if (soln[auxil.A[0].size()-auxil.b.size()+i] != 0) auxphase = true;
    }
    if (!auxphase) break;
    simplex_iteration(auxil,soln);
  }
  //cout << "Phase 2" << endl;
  // Phase 2
  while (true) {
    if (optimal(auxil)) break;
    simplex_iteration(auxil,soln);
  }
  vector<Fraction> final_soln;
  for (unsigned int i = 0; i < (auxil.obj.size()-auxil.b.size()); i++) {
    final_soln.emplace_back(soln[i]);
  }
  //cout << "soln: " << soln << endl;
  return final_soln;
}

vector<Fraction> phase1(const LP& lp_) {
  LP lp = aux(lp_);
  vector<Fraction> soln = aux_soln(lp);
  while (true) {
    // check for phase 1 completion
    bool solved = true;
    for (unsigned int i = soln.size()-lp.b.size(); i < soln.size(); i++) {
      if (soln[i] != 0) solved = false;
    }
    if (solved) return soln;

    phase1_iteration(lp, soln);
  }
}

vector<Fraction> phase2(const LP& lp_, const vector<Fraction> &init_soln) {
  LP lp = lp_;
  vector<Fraction> soln = init_soln;
  while (true) {
    if (optimal(lp)) return soln;
    simplex_iteration(lp, soln);
  }
}

void simplex_iteration(LP &lp, vector<Fraction> &soln) {
  LP_simplify(lp);
  //cout << "LP: " << endl << lp << endl;
  //cout << "soln: " << soln << endl;
  // find k : lp.obj[k] <= 0 && k is not in lp.basis
  unsigned int k = 0;
  bool kchosen = false;
  for (unsigned int i = 0, j = 0; i < lp.obj.size(); i++) {
    //cout << "iteration " << k << endl;
    if (lp.obj[i] > 0 && i != (unsigned) lp.basis[j]) {
      //cout << "(i,k): "<< i << "," << k << endl;
      //cout << "lp.obj[" << i << "]: " << lp.obj[i] << endl;
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

  //cout << "entering k: " << k << endl;
  // TODO: add check for unboundedness
  int m = 0; // leaving value
  Fraction t{INT8_MAX};
  for (unsigned int i = 0; i < lp.A.size(); i++) {
    if (lp.A[i][k] > 0 && Fraction{lp.b[i],lp.A[i][k]} < t) {
      m = lp.basis[i];
      t = Fraction{lp.b[i],lp.A[i][k]};
    }
  }
  //cout << "new val: " << t << endl;
  //cout << "exiting value: " << m << endl;
  
  for (unsigned int i = 0; i < lp.A.size(); i++) {
    soln[lp.basis[i]] = lp.b[i]-(t*lp.A[i][k]);
  }
  ////cout << "soln: " << soln << endl;
  soln[k] = t;
  // add k to the basis, subtracting m
  //cout << "old basis: " << lp.basis << endl;
  vector<int> new_basis;
  for (unsigned int i = 0; i < lp.basis.size(); i++) {
    if (lp.basis[i] != m) {
      //cout << "basis[i]: " << lp.basis[i] << endl;
      new_basis.emplace_back((signed)lp.basis[i]);}
  }
  new_basis.emplace_back((signed)k);
  /*
  if (new_basis.size() < lp.basis.size()) {
    for (unsigned int i = lp.basis.size()-1; i >= new_basis.size()-1; i--) {
      new_basis.emplace_back(lp.basis[i]);
    }
  }
  if (new_basis.size() < lp.basis.size()) {
    for (unsigned int i = 0; ;i++) {
      if (new_basis.size() == lp.basis.size() ||
          i == lp.obj.size()) break;
      if (lp.obj[i] == 0 && !contains(new_basis,i)) {
        new_basis.emplace_back(i);
      }
    }
    sort(new_basis);
  }*/
  sort (new_basis);
  //cout << "new_basis: " << new_basis << endl;
  lp.basis = new_basis;
  LP_simplify(lp);
  //cout << "pre-canon: " << endl << lp << endl;
  canonicalize(lp);
  LP_simplify(lp);
  //cout << "canonicalized" << endl;
  vec_simplify(soln);
}

void phase1_iteration(LP& lp, vector<Fraction> &soln) {
  LP_simplify(lp);
  //cout << "LP: " << endl << lp << endl;
  //cout << "soln: " << soln << endl;
  // find k : lp.obj[k] <= 0 && k is not in lp.basis
  unsigned int k = 0;
  for (unsigned int i = 0, j = 0; i < lp.obj.size(); i++) {
    //cout << "iteration " << k << endl;
    if (lp.obj[i] >= 0 && i != (unsigned) lp.basis[j]) {
      //cout << "(i,k): "<< i << "," << k << endl;
      //cout << "lp.obj[" << i << "]: " << lp.obj[i] << endl;
      j++;
      if (lp.obj[i] > lp.obj[k]) k = i;
    }
    else if (i == (unsigned) lp.basis[j]) j++;
  }
  //cout << "entering k: " << k << endl;
  // TODO: add check for unboundedness
  Fraction t{INT8_MAX};
  for (unsigned int i = 0; i < lp.A.size(); i++) {
    //cout << "iteration " << i << endl;
    //cout << "b[i]: " << lp.b[i] << endl;
    //cout << "A[i][k]: " << lp.A[i][k] << endl;
    if (lp.A[i][k] > 0 && Fraction{lp.b[i],lp.A[i][k]} < t) {
      
      t = Fraction{lp.b[i],lp.A[i][k]};
    }
  }
  //cout << "new val: " << t << endl;
  
  for (unsigned int i = 0; i < lp.A.size(); i++) {
    soln[lp.basis[i]] = lp.b[i]-(t*lp.A[i][k]);
  }
  //cout << "soln: " << soln << endl;
  soln[k] = t;
  // add k to the basis, subtracting m
  vector<int> new_basis;
  for (unsigned int i = 0; i < soln.size(); i++) {
    //cout << "soln[" << i << "]: " << soln[i] << endl;
    if (soln[i] > Fraction{0}) {
      //cout << "in basis" << endl;
      new_basis.emplace_back(i);}
  }
  /*
  if (new_basis.size() < lp.basis.size()) {
    for (unsigned int i = lp.basis.size()-1; i >= new_basis.size()-1; i--) {
      new_basis.emplace_back(lp.basis[i]);
    }
  }*/
  if (new_basis.size() < lp.basis.size()) {
    for (unsigned int i = 0; ;i++) {
      if (new_basis.size() == lp.basis.size() ||
          i == lp.obj.size()) break;
      if (lp.obj[i] == 0 && !contains(new_basis,i)) {
        new_basis.emplace_back(i);
      }
    }
    sort(new_basis);
  }
  //cout << "new_basis: " << new_basis << endl;
  lp.basis = new_basis;
  LP_simplify(lp);
  //cout << "pre-canon: " << endl << lp << endl;
  canonicalize(lp);
  LP_simplify(lp);
  //cout << "canonicalized" << endl;
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
