#include "simplex.h"
#include <string>

using namespace std;

int main() {
  string cmd;
  while (cin >> cmd) {
    if (cmd == "q" || cmd == "quit") break;
    else if (cmd == "canonicalize") {
      LP lp;
      cin >> lp;
      //cout << "before canon:" << endl;
      //cout << lp << endl;
      canonicalize(lp);
      cout << lp << endl;
    }
    else if (cmd == "readint") {
      vector<int> v;
      cin >> v;
      cout << v << endl;
    }
    else if (cmd == "readLP") {
      LP lp;
      cin >> lp;
      cout << lp;
    }
    else if (cmd == "aux") {
      LP lp;
      cin >> lp;
      LP aux_lp = aux(lp);
      vector<Fraction> soln = aux_soln(aux_lp);
      vec_simplify(soln);
      cout << soln << endl;
    }
    else if (cmd == "canonform") {
      LP lp;
      cin >> lp;
      if (canonical_form(lp)) cout << "true" << endl;
      else cout << "false" << endl; 
    }
    else if (cmd == "solve") {
      LP lp;
      cin >> lp;
      vector<Fraction> soln = simplex_solve(lp);
      vec_simplify(soln);
      cout << soln << endl;
      //cout << "obj val: " << soln*lp.obj + lp.obj_const << endl;
      //cout << "LP: " << endl << lp << endl;
    }
    else if (cmd == "iter") {
      LP lp;
      vector<Fraction> soln;
      cin >> lp;
      cin >> soln;
      simplex_iteration(lp,soln);
      cout << "LP:" << endl << lp << endl;
      cout << "soln: " << soln << endl;
    }
    else if (cmd == "phase1") {
      LP lp;
      cin >> lp;
      vector<Fraction> soln = phase1(lp);
      vec_simplify(soln);
      cout << soln << endl;
    }
    else if (cmd == "phase2") {
      LP lp;
      vector<Fraction> soln;
      cin >> lp;
      cin >> soln;
      vector<Fraction> endsoln = phase2(lp, soln);
      vec_simplify(endsoln);
      cout << endsoln << endl;
    }
    else if (cmd == "sort") {
      vector<int> vec;
      cin >> vec;
      sort(vec);
      cout << vec << endl;
    }
  }
  return 0;
}