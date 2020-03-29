#include "linear_systems.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  string cmd;
  while (cin >> cmd) {
    if (cmd == "=") {
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
      cout << m << endl;
    }
    else if (cmd == "readvec") {
      vector<Fraction> vec;
      cin >> vec;
      cout << vec << endl;
    }
  }
  return 0;
}
