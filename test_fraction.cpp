#include <iostream>
#include "fraction.h"

using namespace std;

void test1() {
  Fraction frac1(3,4);
  Fraction frac2(1,2);
  Fraction frac3(2,4);
  if (frac1 == frac2) cout << "failure" << endl;
  else cout << "success" << endl;
  if (frac2 == frac3) cout << "failure" << endl;
  else cout << "success" << endl;
  if (frac1 == frac3) cout << "failure" << endl;
  else cout << "success" << endl;
}

void test2() {
  Fraction frac(1,2);
  frac = 4*frac;
  if (frac.getNum() == 4 && frac.getDenom() == 2) cout << "success" << endl;
  else cout << "failure" << endl;
}

void test3() {
  //cout << "test3" << endl;
  Fraction frac1(2,2);
  Fraction frac2(1,2);
  Fraction frac3 = frac1 - frac2;
  frac3.simplify();
  frac2.simplify();
  //cout << "after setting frac3" << endl;
  if (frac2 == frac3) cout << "success" << endl;
  else cout << "failure - frac2: " << frac2 << "frac3: " << frac3 << endl;
  frac1 -= frac2;
  frac1.simplify();
  frac3.simplify();
  if (frac1 == frac3) cout << "success" << endl;
  else cout << "failure" << endl;
}

void test4() {
  Fraction frac1(1,2);
  Fraction frac2 = frac1;
  Fraction frac3(0,0);
  Fraction frac4(1,1);
  frac3 = frac1+frac2;
  frac3.simplify();
  if (frac3 == frac4) cout << "success" << endl;
  else cout << "failure" << endl;
}

void test5() {
  cout << "test5 - operator /:" << endl;
  Fraction frac1(2,1);
  Fraction frac2(2);
  Fraction frac3 = frac1/frac2;
  frac3.simplify();
  if (frac3 == Fraction(1,1)) cout << "success" << endl;
  else cout << "failure - frac3: " << frac3 << endl;
}

void test6() {
  cout << "test6 - operator /:" << endl;
  Fraction frac1(5);
  Fraction frac2(3);
  Fraction frac3 = frac1 / frac2;
  if (frac3 == Fraction(5,3)) cout << "success" << endl;
  else cout << "failure - frac3: " << frac3 << endl;
}

void test7() {
  cout << "test7 - operator /:" << endl;
  Fraction frac1(4);
  Fraction frac2(2);
  Fraction frac3 = frac1/frac2;
  if (frac3 == Fraction(4,2)) cout << "success" << endl;
  else cout << "failure - frac3: " << frac3 << endl;
  frac3.simplify();
  if (frac3 == Fraction(2)) cout << "success" << endl;
  else cout << "failure - frac3: " << frac3 << endl;
}

void test8() {
  cout << "test8 - operator /: " << endl;
  Fraction frac1(0);
  Fraction frac2(3);
  Fraction frac3 = frac1 / frac2;
  frac3.simplify();
  if (frac3 == Fraction(0)) cout << "success" << endl;
  else cout << "failure - frac3: " << frac3 << endl;
}

void test9() {
  cout << "test9 - operator *: " << endl;
  Fraction frac1(2);
  Fraction frac2(1,2);
  Fraction frac3 = frac1*frac2;
  if (frac3 == Fraction(2,2)) cout << "success" << endl;
  else cout << "failure - frac3: " << frac3 << endl;
  frac3.simplify();
  if (frac3 == Fraction(1)) cout << "success" << endl;
  else cout << "failure - frac3: " << frac3 << endl;
}

void test10() {
  cout << "test 10 - operator * and operator -" << endl;
  Fraction frac1(2);
  Fraction frac2(3);
  Fraction frac3(2);
  Fraction frac4 = frac1 - (frac2*frac3);
  if (frac4 == Fraction(-4)) cout << "success" << endl;
  else cout << "failure - frac4: " << frac4 << endl; 
}

void test11() {
  cout << "test 11 - subtracting negatives: " << endl;
  Fraction frac1(1,2);
  Fraction frac2(-3,2);
  Fraction frac3(2);
  Fraction frac4 = frac1 - frac2;
  frac4.simplify();
  if (frac4 == frac3) cout << "success" << endl;
  else cout << "failure - frac4: " << frac4 << endl;
}

void test12() {
  cout << "test 12 - simplify: " << endl;
  Fraction frac1(0,-4);
  Fraction frac2(0,1);
  frac1.simplify();
  if (frac1 == frac2) cout << "success" << endl;
  else cout << "failure - frac1: " << frac1 << endl;
}

void test13() {
  cout << "test 13 - simplify: " << endl;
  Fraction frac1(0,-1);
  Fraction frac2(0,1);
  frac1.simplify();
  if (frac1 == frac2) cout << "success" << endl;
  else cout << "failure - frac1: " << frac1 << endl;
}

void test14() {
  cout << "test 14 - simplify: " << endl;
  Fraction frac1(-1,-1);
  Fraction frac2(1);
  frac1.simplify();
  if (frac1 == frac2) cout << "success" << endl;
  else cout << "failure - frac1: " << frac1 << endl;
}

void test15() {
  cout << "test 15 - simplify: " << endl;
  Fraction frac1(-4,-4);
  Fraction frac2(1,1);
  frac1.simplify();
  if (frac1 == frac2) cout << "success" << endl;
  else cout << "failure - frac1: " << frac1 << endl;
}

void test16() {
  cout << "test 16 - simplify: " << endl;
  Fraction frac1(0,-3);
  Fraction frac2(0);
  frac1.simplify();
  if (frac1 == frac2) cout << "success" << endl;
  else cout << "failure - frac1: " << frac1 << endl;
}

void test17() {
  cout << "test 17 - simplify: " << endl;
  Fraction frac1(-2,2);
  Fraction frac2(-1);
  frac1.simplify();
  if (frac1 == frac2) cout << "success" << endl;
  else cout << "failure - frac1: " << frac1 << endl;
}

void test18() {
  cout << "test 18 - simplify: " << endl;
  Fraction frac1(3,-3);
  Fraction frac2(-1);
  frac1.simplify();
  if (frac1 == frac2) cout << "success" << endl;
  else cout << "failure - frac1: " << frac1 << endl;
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();
  test13();
  test14();
  test15();
  test16();
  test17();
  test18();
  return 0;
}