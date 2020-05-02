#include "matrix_tools.h"

typedef vector<vector<Fraction>> matrix;

void test1() {
  cout << "inverse: " << endl;
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  row1.push_back(Fraction(1,1));
  row1.push_back(Fraction(1,1));
  row1.push_back(Fraction(0,1));
  vector<Fraction> row2;
  row2.push_back(Fraction(2,1));
  row2.push_back(Fraction(1,1));
  row2.push_back(Fraction(1,1));
  vector<Fraction> row3;
  row3.push_back(Fraction(-1,1));
  row3.push_back(Fraction(1,1));
  row3.push_back(Fraction(0,1));
  m.push_back(row1);
  m.push_back(row2);
  m.push_back(row3);

  vector<vector<Fraction>> inv;
  vector<Fraction> row4;
  row4.push_back(Fraction(1,2));
  row4.push_back(Fraction(0,1));
  row4.push_back(Fraction(-1,2));
  vector<Fraction> row5;
  row5.push_back(Fraction(1,2));
  row5.push_back(Fraction(0,1));
  row5.push_back(Fraction(1,2));
  vector<Fraction> row6;
  row6.push_back(Fraction(-3,2));
  row6.push_back(Fraction(1,1));
  row6.push_back(Fraction(1,2));
  inv.push_back(row4);
  inv.push_back(row5);
  inv.push_back(row6);
  vector<vector<Fraction>> inv_m = inverse(m);
  matrix_simplify(inv_m);
  if (!matrix_equal(inv_m, inv)) {
    cout << "failure - m: " << endl << m << endl;
    cout << "inv(m): " << endl << inv_m << endl;
    cout << endl << "inv: " << endl << inv << endl;
  }
  else cout << "success" << endl;
}

void test2() {
  cout << "subset: " << endl;
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  vector<Fraction> row2;
  for (int i = 0; i<4; i++) row1.push_back(i);
  for (int i = 4; i<8; i++) row2.push_back(i);
  m.push_back(row1);
  m.push_back(row2);

  vector<vector<Fraction>> sub;
  vector<Fraction> row3;
  vector<Fraction> row4;
  for (int i = 2; i<4; i++) row3.push_back(i);
  for (int i = 6; i<8; i++) row4.push_back(i);
  sub.push_back(row3);
  sub.push_back(row4);

  vector<int> basis;
  basis.push_back(2);
  basis.push_back(3);

  vector<vector<Fraction>> sub_ = subset(m, basis);

  if (matrix_equal(sub_, sub)) cout << "success" << endl;
  else {
    cout << "failure" << endl;
    cout << "sub: " << sub << endl << "subset(m): " << sub_ << endl;
  }
}

void test3() {
  cout << "test 3 - swapping rows: " << endl;
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  vector<Fraction> row2;
  vector<Fraction> row3;
  m.push_back(row1);
  m.push_back(row2);
  m.push_back(row3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) m[i].push_back(Fraction((i+1)*(j+1)));
  }
  vector<Fraction> temp = m[0];
  m[0] = m[1];
  m[1] = temp;

  vector<vector<Fraction>> m2;
  vector<Fraction> row_1;
  vector<Fraction> row_2;
  vector<Fraction> row_3;
  m2.push_back(row_1);
  m2.push_back(row_2);
  m2.push_back(row_3);
  for (int i = 0; i < 3; i++) m2[0].push_back(Fraction(2*i+2));
  for (int i = 0; i < 3; i++) m2[1].push_back(Fraction(i+1));
  for (int i = 0; i < 3; i++) m2[2].push_back(Fraction(i*3+3));
  if (matrix_equal(m2, m)) cout << "success" << endl;
  else cout << "failure - m: " << m << endl << "m2: " << m2 << endl;
}

void test4() {
  cout << "test 4 - swapping rows: " << endl;
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  vector<Fraction> row2;
  vector<Fraction> row3;
  m.push_back(row1);
  m.push_back(row2);
  m.push_back(row3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) m[i].push_back(Fraction(3*i+j));
  }
  vector<Fraction> temp = m[1];
  m[1] = m[2];
  m[2] = temp;

  vector<vector<Fraction>> m2;
  vector<Fraction> row_1;
  vector<Fraction> row_2;
  vector<Fraction> row_3;
  m2.push_back(row_1);
  m2.push_back(row_2);
  m2.push_back(row_3);
  for (int i = 0; i < 3; i++) m2[0].push_back(Fraction(i));
  for (int i = 0; i < 3; i++) m2[1].push_back(Fraction(i+6));
  for (int i = 0; i < 3; i++) m2[2].push_back(Fraction(i+3));

  if (matrix_equal(m2, m)) cout << "success" << endl;
  else cout << "failure - m: " << endl << m << "m2: " << endl << m2;
}

void test5() {
  cout << "test 5 - inner product: " << endl;
  vector<Fraction> v1;
  vector<Fraction> v2;
  for (int i = 0; i < 3; i++) v1.push_back(Fraction(i));
  for (int i = 0; i < 3; i++) v2.push_back(Fraction(3+i));
  Fraction c = inner_product(v1, v2);
  c.simplify();
  if (c == Fraction(14)) cout << "success" << endl;
  else cout << "failure: v1*v2: " << c << endl;
}

void test6() {
  cout << "test 6 - Matrix*Vector: " << endl;
  vector<Fraction> v;
  for (int i = 1; i < 4; i++) v.push_back(Fraction(i));
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  vector<Fraction> row2;
  vector<Fraction> row3;
  m.push_back(row1);
  m.push_back(row2);
  m.push_back(row3);
  for (int i = 0; i < 3; i++) {
    for (int j = 1; j < 4; j++) m[i].push_back(Fraction(i*3+j));
  }
  
  vector<Fraction> soln;
  soln.push_back(Fraction(14));
  soln.push_back(Fraction(32));
  soln.push_back(Fraction(50));

  if (vec_equal(soln, multiply(m, v))) cout << "success" << endl;
  else cout << "failure - Mv: " << endl << multiply(m,v) << endl << "m:"<<endl<<m<<endl<<"v: " << v << endl;
}

void test7() {
  cout << "test 7 - Matrix*vector: " << endl;
  vector<Fraction> v;
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  vector<Fraction> row2;
  vector<Fraction> row3;
  m.push_back(row1);
  m.push_back(row2);
  m.push_back(row3);
  v.push_back(Fraction(0));
  v.push_back(Fraction(1));
  v.push_back(Fraction(0));
  for (int i = 0; i < 3; i++) {
    for (int j = 1; j < 4; j++) m[i].push_back(3*i+j);
  }

  vector<Fraction> soln;
  soln.push_back(2);
  soln.push_back(5);
  soln.push_back(8);
  if (vec_equal(soln, multiply(m, v))) cout << "success" << endl;
  else cout << "failure - m: " << endl << m << endl << "v: " << endl << v << endl << "Mv: " << endl << multiply(m, v) << endl;
}

void test8() {
  cout << "test8 - inverse: " << endl;
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  row1.push_back(Fraction(1));
  row1.push_back(Fraction(2));
  m.push_back(row1);
  vector<Fraction> row2;
  row2.push_back(Fraction(3));
  row2.push_back(Fraction(5));
  m.push_back(row2);

  vector<vector<Fraction>> inv;
  vector<Fraction> row3;
  row3.push_back(Fraction(-5));
  row3.push_back(Fraction(2));
  inv.push_back(row3);
  vector<Fraction> row4;
  row4.push_back(Fraction(3));
  row4.push_back(Fraction(-1));
  inv.push_back(row4);

  vector<vector<Fraction>> inv_m = inverse(m);
  if (inv_m == inv) cout << "success" << endl;
  else cout << "failure - inv_m: " << endl << inv_m << endl;
}

void test9() {
  cout << "test 9 - inverse: " << endl;
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  row1.push_back(Fraction(4));
  row1.push_back(Fraction(5));
  row1.push_back(Fraction(2));
  row1.push_back(Fraction(5));
  m.push_back(row1);
  vector<Fraction> row2;
  row2.push_back(Fraction(10));
  row2.push_back(Fraction(123));
  row2.push_back(Fraction(78));
  row2.push_back(Fraction(4));
  m.push_back(row2);
  vector<Fraction> row3;
  row3.push_back(Fraction(80));
  row3.push_back(Fraction(43));
  row3.push_back(Fraction(51));
  row3.push_back(Fraction(89));
  m.push_back(row3);
  vector<Fraction> row4;
  row4.push_back(Fraction(34));
  row4.push_back(Fraction(2));
  row4.push_back(Fraction(2));
  row4.push_back(Fraction(2));
  m.push_back(row4);

  vector<vector<Fraction>> inv;
  vector<Fraction> row5;
  row5.push_back(Fraction(1118,429027));
  row5.push_back(Fraction(-46,143009));
  row5.push_back(Fraction(-119,143009));
  row5.push_back(Fraction(26735,858054));
  inv.push_back(row5);
  vector<Fraction> row6;
  row6.push_back(Fraction(36082,143009));
  row6.push_back(Fraction(407,143009));
  row6.push_back(Fraction(-2056,143009));
  row6.push_back(Fraction(473,143009));
  inv.push_back(row6);
  vector<Fraction> row7;
  row7.push_back(Fraction(-173195,429027));
  row7.push_back(Fraction(1242,143009));
  row7.push_back(Fraction(3213,143009));
  row7.push_back(Fraction(-4300,429027));
  inv.push_back(row7);
  vector<Fraction> row8;
  row8.push_back(Fraction(45943,429027));
  row8.push_back(Fraction(-867,143009));
  row8.push_back(Fraction(866,143009));
  row8.push_back(Fraction(-10753,429027));
  inv.push_back(row8);

  vector<vector<Fraction>> inv_m = inverse(m);
  if (inv_m == inv) cout << "success" << endl;
  else cout << "failure - inv_m: " << endl << inv_m << endl;
}

void test10() {
  cout << "test 10 - transpose" << endl;
  matrix m;
  vector<Fraction> row1;
  row1.push_back(1);
  row1.push_back(0);
  row1.push_back(0);
  vector<Fraction> row2;
  row2.push_back(0);
  row2.push_back(1);
  row2.push_back(0);
  vector<Fraction> row3;
  row3.push_back(0);
  row3.push_back(0);
  row3.push_back(1);
  m.push_back(row1);
  m.push_back(row2);
  m.push_back(row3);

  if (m == transpose(m)) cout << "success" << endl;
  else cout << "failure - trans(m): " << endl << transpose(m) << endl;
}

void test11() {
  cout << "test 11 - transpose" << endl;
  matrix m;
  vector<Fraction> row1;
  row1.push_back(1);
  row1.push_back(2);
  row1.push_back(3);
  vector<Fraction> row2;
  row2.push_back(4);
  row2.push_back(5);
  row2.push_back(6);
  vector<Fraction> row3;
  row3.push_back(7);
  row3.push_back(8);
  row3.push_back(9);
  m.push_back(row1);
  m.push_back(row2);
  m.push_back(row3);

  matrix transp;
  vector<Fraction> row1_;
  row1_.push_back(1);
  row1_.push_back(4);
  row1_.push_back(7);
  vector<Fraction> row2_;
  row2_.push_back(2);
  row2_.push_back(5);
  row2_.push_back(8);
  vector<Fraction> row3_;
  row3_.push_back(3);
  row3_.push_back(6);
  row3_.push_back(9);
  transp.push_back(row1_);
  transp.push_back(row2_);
  transp.push_back(row3_);

  if (transp == transpose(m)) cout << "success" << endl;
  else cout << "failure: - intended transpose: " << endl << transpose(m) << endl << "actual transpose: " << transp << endl;
}

void test12() {
  cout << "test 12 - Matrix Matrix Multiplication" << endl;
  matrix m1;
  matrix m2;
  
  vector<Fraction> row1_1;
  row1_1.push_back(1);
  row1_1.push_back(2);
  row1_1.push_back(3);
  vector<Fraction> row1_2;
  row1_2.push_back(4);
  row1_2.push_back(5);
  row1_2.push_back(6);
  vector<Fraction> row1_3;
  row1_3.push_back(7);
  row1_3.push_back(8);
  row1_3.push_back(9);
  m1.push_back(row1_1);
  m1.push_back(row1_2);
  m1.push_back(row1_3);

  vector<Fraction> row2_1;
  row2_1.push_back(1);
  row2_1.push_back(0);
  row2_1.push_back(0);
  vector<Fraction> row2_2;
  row2_2.push_back(0);
  row2_2.push_back(1);
  row2_2.push_back(0);
  vector<Fraction> row2_3;
  row2_3.push_back(0);
  row2_3.push_back(0);
  row2_3.push_back(1);
  m2.push_back(row2_1);
  m2.push_back(row2_2);
  m2.push_back(row2_3);

  if (multiply(m1, m2) == m1) cout << "success" << endl;
  else cout << "failure - intended product" << endl << m1 << "actual" << endl << multiply(m1,m2) << endl;
}

void test13() {
  cout << "test 13 - Matrix Matrix multiplication" << endl;
  vector<vector<Fraction>> m;
  vector<Fraction> row1;
  row1.push_back(Fraction(3));
  row1.push_back(Fraction(3));
  row1.push_back(Fraction(3));
  m.push_back(row1);
  vector<Fraction> row2;
  row2.push_back(Fraction(1));
  row2.push_back(Fraction(2));
  row2.push_back(Fraction(3));
  m.push_back(row2);
  vector<Fraction> row3;
  row3.push_back(Fraction(1));
  row3.push_back(Fraction(1));
  row3.push_back(Fraction(3));
  m.push_back(row3);

  vector<vector<Fraction>> L;
  vector<Fraction> L_1;
  L_1.push_back(Fraction(1));
  L_1.push_back(Fraction(0));
  L_1.push_back(Fraction(0));
  L.push_back(L_1);
  vector<Fraction> L_2;
  L_2.push_back(Fraction(1,3));
  L_2.push_back(Fraction(1));
  L_2.push_back(Fraction(0));
  L.push_back(L_2);
  vector<Fraction> L_3;
  L_3.push_back(Fraction(1,3));
  L_3.push_back(Fraction(0));
  L_3.push_back(Fraction(1));
  L.push_back(L_3);

  vector<vector<Fraction>> U;
  vector<Fraction> U_1;
  U_1.push_back(Fraction(3));
  U_1.push_back(Fraction(3));
  U_1.push_back(Fraction(3));
  U.push_back(U_1);
  vector<Fraction> U_2;
  U_2.push_back(Fraction(0));
  U_2.push_back(Fraction(1));
  U_2.push_back(Fraction(2));
  U.push_back(U_2);
  vector<Fraction> U_3;
  U_3.push_back(Fraction(0));
  U_3.push_back(Fraction(0));
  U_3.push_back(Fraction(2));
  U.push_back(U_3);

  if (multiply(L,U) == m) cout << "success" << endl;
  else {
    cout << "failure - intended product: " << endl << m << endl;
    cout << "actual product: " << multiply(L,U) << endl;
  }
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
  //test9();
  test10();
  test11();
  test12();
  test13();
  return 0;
}