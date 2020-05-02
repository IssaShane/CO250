#include "linear_systems.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  string cmd;
  while (cin >> cmd) {
    if (cmd == "quit" || cmd == "q") break;
    else if (cmd == "=") {
      matrix m1, m2;
      cin >> m1;
      cin >> m2;
      if (matrix_equal(m1, m2)) cout << "true" << endl;
      else cout << "false" << endl;
    }
    else if (cmd == "eliminate") {
      matrix m;
      cin >> m;
      int i;
      cin >> i;
      eliminate_col(m,i);
      cout << m << endl;
    }
    else if (cmd == "upper") {
      matrix m;
      cin >> m;
      cout << upper_triangular(m) << endl;
    }
    else if (cmd == "lower") {
      matrix m;
      cin >> m;
      cout << lower_triangular(m) << endl;
    }
    else if (cmd == "print") {
      matrix m;
      cin >> m;
      cout << "dim: " << m.size() << "x" << m[0].size() << endl;
      cout << m << endl;
    }
    else if (cmd == "printsys") {
      matrix A;
      vector<Fraction> b;
      cin >> A;
      cin >> b;
      
      cout << "A: [" << A.size() << "x" << A[0].size() << "]" << endl << A << endl; 
      cout << "b: [" << b.size() << "]: " << b << endl;
    }
    else if (cmd == "readvec") {
      vector<Fraction> vec;
      cin >> vec;
      cout << vec << endl;
    }
    else if (cmd == "solve") {
      vector<Fraction> b;
      matrix A;
      cin >> b;
      cin >> A;
      //cout << "A dim" << A.size() << "x" << A[0].size() << endl;
      vector<Fraction> x = LU_Solve(A,b);
      vec_simplify(x);
      cout << x << endl;
    }
    else if (cmd == "inverse") {
      matrix m;
      cin >> m;
      matrix m_ = inverse(m);
      matrix_simplify(m_);
      cout << m_ << endl;
    }
    else if (cmd == "forwardsub") {
      matrix m;
      vector<Fraction> v;
      cin >> v;
      cin >> m;
      vector<Fraction> soln = forward_sub(m,v);
      vec_simplify(soln);
      cout << soln << endl;
    }
    else if (cmd == "backwardsub") {
      matrix m;
      vector<Fraction> v;
      cin >> v;
      cin >> m;
      vector<Fraction> soln = backward_sub(m,v);
      vec_simplify(soln);
      cout << soln << endl;
    }
  }
  return 0;
}
