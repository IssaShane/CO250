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
        else if (cmd == "subset") {
            matrix A;
            vector<int> basis;
            cin >> A;
            cin >> basis;
            cout << subset(A,basis) << endl;
        }
        else if (cmd == "swaprows") {
            matrix A;
            int i,j;
            cin >> A;
            cin >> i;
            cin >> j;
            swap_rows(A,i,j);
            cout << A << endl;
        }
        else if (cmd == "inverse") {
            matrix A;
            cin >> A;
            cout << inverse(A) << endl;
        }
        else if (cmd == "innerproduct") {
            vector<Fraction> v1;
            vector<Fraction> v2;
            char c;
            while (cin >> c) if (c == '[') break;
            cin >> v1; 
            while (cin >> c) if (c == '[') break;
            cin >> v2;
            Fraction prod = inner_product(v1,v2);
            prod.simplify();
            cout << prod << endl;
        }
        else if (cmd == "multfrac") {
            Fraction f1{-3};
            Fraction f2{1};
            cin >> f1;
            //cout << "f1: " << f1 << endl;
            cin >> f2;
            //cout << "f2: " << f2 << endl;
            Fraction product = f1*f2;
            product.simplify();
            cout << product << endl;
        }
        else if (cmd == "addfrac") {
            Fraction f1{0};
            Fraction f2{0};
            cin >> f1;
            cin >> f2;
            Fraction sum = f1 + f2;
            sum.simplify();
            cout << sum << endl;
        }
        else if (cmd == "divfrac") {
            Fraction f1{-3};
            Fraction f2{1};
            cin >> f1;
            cin >> f2;
            Fraction quotient = f1/f2;
            quotient.simplify();
            cout << quotient << endl;
        }
        else if (cmd == "subfrac") {
            Fraction f1{0};
            Fraction f2{0};
            cin >> f1;
            cin >> f2;
            Fraction diff = f1 - f2;
            diff.simplify();
            cout << diff << endl;
        }
    }
    return 0;
}