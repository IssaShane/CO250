#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "../linear_sys/linear_systems.h"

struct LP {
  matrix A;
  vector<Fraction> b;
  vector<Fraction> obj;
  Fraction obj_const{0};
  vector<int> basis;
};

// LP Manipulation
vector<Fraction> aux(matrix,vector<Fraction>);
bool canonical_form(const LP&);
void canonicalize(LP &lp);
void LP_simplify(LP &lp);

// Input / Output
std::istream& operator>>(std::istream&,LP&);
std::ostream& operator<<(std::ostream&,const LP&);

#endif