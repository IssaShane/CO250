#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
  private:
    long long int num;
    long long int denom;

  public:
    Fraction(int num, int denom);
    Fraction(int num);
    Fraction(const Fraction &other);
    Fraction &operator-=(const Fraction &b);
    Fraction &operator+=(const Fraction &b);
    Fraction &operator*=(int b);
    Fraction &operator*=(const Fraction &b);
    Fraction &operator/=(const Fraction &b);
    void simplify();

    int getNum() const;
    int getDenom() const;
};

Fraction operator+(const Fraction &a, const Fraction & b);
Fraction operator-(const Fraction &a, const Fraction &b);
Fraction operator*(int c, const Fraction &a);
Fraction operator*(const Fraction &a, const Fraction &b);
Fraction operator/(const Fraction &a, const Fraction &b);
bool operator==(const Fraction &a, const Fraction &b);
bool operator!=(const Fraction &a, const Fraction &b);
bool operator<(const Fraction &a, const Fraction &b);
bool operator>(const Fraction &a, const Fraction &b);
bool operator<=(const Fraction &a, const Fraction &b);
bool operator>=(const Fraction &a, const Fraction &b);
std::ostream &operator<<(std::ostream &str, const Fraction &a);
std::istream &operator>>(std::istream &str, Fraction &a);


#endif