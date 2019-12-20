#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
  private:
    int num;
    int denom;

  public:
    Fraction(int num, int denom);
    Fraction(const Fraction &other);
    Fraction operator-=(const Fraction &b);
    Fraction operator+=(const Fraction &b);
    Fraction operator*=(int b);
    void simplify();

    int getNum() const;
    int getDenom() const;
};

Fraction operator+(const Fraction & a, const Fraction & b);
Fraction operator-(const Fraction &a, const Fraction &b);
Fraction operator*(int c, Fraction &a);
Fraction operator*(Fraction &a, Fraction &b);
Fraction operator/(Fraction &a, Fraction &b);
bool operator==(const Fraction &a, const Fraction &b);
bool operator!=(const Fraction &a, const Fraction &b);
bool operator<(const Fraction &a, const Fraction &b);
bool operator>(const Fraction &a, const Fraction &b);
bool operator<=(const Fraction &a, const Fraction &b);
bool operator>=(const Fraction &a, const Fraction &b);
std::ostream &operator<<(std::ostream &str, const Fraction &a);


#endif