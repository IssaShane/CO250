#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "simplex.cpp"
#include <vector>

using namespace std;

bool vec_equal(vector<int> a, vector<int> b) {
  if (a.size() != b.size()) {
    return false;
  }

  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

vector<int> & vec_fill(int a[], int size) {
  vector<int> vec;
  for (int i = 0; i < size; i++) {
    vec.push_back(a[i]);
  }
  return vec;
}

TEST_CASE("Auxiliary Solution", "[aux]") {
  vector<int> solution;
  solution.push_back(0);
  solution.push_back(0);
  solution.push_back(6);
  solution.push_back(7);
  vector<vector<int>> arg;
  vector<int> row1;
  row1.push_back(1);
  row1.push_back(2);
  vector<int> row2;
  row2.push_back(3);
  row2.push_back(4);
  vector<int> row3;
  row3.push_back(6);
  row3.push_back(7);
  arg.push_back(row1);
  arg.push_back(row2);
  REQUIRE(solution == aux(arg, row3));
}