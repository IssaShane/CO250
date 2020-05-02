#include "matrix_tools.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    string cmd;
    while (cin >> cmd) {
        if (cmd == "quit"||cmd == "q") break;
        else if (cmd == "transpose") {
            matrix A;
            cin >> A;
            cout << transpose(A) << endl;
        }
        else if (cmd == "matrixmult") {
            matrix A, B;
            cin >> A;
            cin >> B;
            matrix product = A*B;
            matrix_simplify(product);
            cout << product << endl;
        }
        else if (cmd == "vecmult") {
            matrix A;
            vector<Fraction> vec;
            cin >> A;
            cin >> vec;
            vector<Fraction> product = multiply(A,vec);
            vec_simplify(product);
            cout << product << endl;
        }
    }
    return 0;
}
