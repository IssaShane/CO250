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
      matrix A;
      cin >> A;
      vector<Fraction> vec;
      cin >> vec;
      cout << aux(A,vec) << endl;
    }
    else if (cmd == "canonform") {
      LP lp;
      cin >> lp;
      if (canonical_form(lp)) cout << "true" << endl;
      else cout << "false" << endl; 
    }
  }
  return 0;
}