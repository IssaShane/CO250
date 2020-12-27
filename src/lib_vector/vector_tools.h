#ifndef VECTOR_TOOLS_H
#define VECTOR_TOOLS_H

#include <vector>
#include <sstream>
#include "fraction.h"

typedef std::vector<std::vector<Fraction>> matrix;

// Vector Operations
void vec_simplify(std::vector<Fraction>&);
bool vec_equal(std::vector<Fraction> a, std::vector<Fraction> b);
std::vector<Fraction> subset_compliment(const std::vector<int>&, const std::vector<Fraction>&);
bool contains(const std::vector<int>&, int);

// Sorting
void sort(std::vector<int>&);

// Vector Arithmatic
std::vector<Fraction> operator+(const std::vector<Fraction>&, const std::vector<Fraction> &);
std::vector<Fraction> operator-(const std::vector<Fraction>&, const std::vector<Fraction>&);
std::vector<Fraction> operator*(const Fraction &c, const std::vector<Fraction>& v);
std::vector<Fraction> operator/(const std::vector<Fraction>& v, const Fraction &c);
Fraction operator*(const std::vector<Fraction> &a, const std::vector<Fraction> &b);
int inner_product(const std::vector<int>&, const std::vector<int>&);
Fraction inner_product(const std::vector<Fraction>&, const std::vector<Fraction>&);

// Vector x Vector Comparison
bool operator==(const std::vector<Fraction> &a, const std::vector<Fraction> &b);
bool operator<(const std::vector<Fraction>& a, const std::vector<Fraction> &b);
bool operator>(const std::vector<Fraction>& a, const std::vector<Fraction> &b);
bool operator<=(const std::vector<Fraction>& a, const std::vector<Fraction> &b);
bool operator>=(const std::vector<Fraction>& a, const std::vector<Fraction> &b);

// Vector x Fraction Comparison
bool operator==(const std::vector<Fraction> &a, const Fraction &b);
bool operator<(const std::vector<Fraction>& a, const Fraction &b);
bool operator>(const std::vector<Fraction>& a, const Fraction &b);
bool operator<=(const std::vector<Fraction>& a, const Fraction &b);
bool operator>=(const std::vector<Fraction>& a, const Fraction &b);

// Input / Output
std::ostream &operator<<(std::ostream &str, const std::vector<Fraction> &v);
std::istream &operator>>(std::istream&, std::vector<Fraction>&);
std::istream &operator>>(std::istream&, std::vector<int>&);
std::ostream &operator<<(std::ostream &str, const std::vector<int> &v);

#endif