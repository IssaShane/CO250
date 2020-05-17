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

// LP Conditions
bool canonical_form(const LP&);
bool optimal(const LP&);
bool unbounded(const LP&);

// LP Manipulation
LP aux(const LP&);
vector<Fraction> aux_soln(const LP&);
LP sef(const LP&);

void canonicalize(LP &lp);
void LP_simplify(LP &lp);
vector<Fraction> simplex_solve(LP &lp);
vector<Fraction> phase1(LP&);
vector<Fraction> phase2(LP&, vector<Fraction>&);
void simplex_iteration(LP &lp, vector<Fraction> &soln);
void phase1_iteration(LP&, vector<Fraction> &soln);

// Input / Output
std::istream& operator>>(std::istream&,LP&);
std::ostream& operator<<(std::ostream&,const LP&);

#endif