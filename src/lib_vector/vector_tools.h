#ifndef VECTOR_TOOLS_H
#define VECTOR_TOOLS_H

#include <vector>
#include <sstream>
#include "fraction.h"

typedef std::vector<std::vector<Fraction>> matrix;

// Vector Operations
void vec_simplify(std::vector<Fraction>&);
bool vec_equal(std::vector<Fraction> a, std::vector<Fraction> b);

// Vector Arithmatic
std::vector<Fraction> operator+(const std::vector<Fraction>&, const std::vector<Fraction> &);
std::vector<Fraction> operator-(const std::vector<Fraction>&, const std::vector<Fraction>&);
Fraction operator*(const std::vector<Fraction> &a, const std::vector<Fraction> &b);
int inner_product(const std::vector<int>&, const std::vector<int>&);
Fraction inner_product(const std::vector<Fraction>&, const std::vector<Fraction>&);

// Input / Output
std::ostream &operator<<(std::ostream &str, const std::vector<Fraction> &v);
std::istream &operator>>(std::istream&, std::vector<Fraction>&);
std::istream &operator>>(std::istream&, std::vector<int>&);
std::ostream &operator<<(std::ostream &str, const std::vector<int> &v);

#endif