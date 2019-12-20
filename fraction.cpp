#include "fraction.h"

Fraction::Fraction(int num, int denom) {
  this->num = num;
  this->denom = denom;
}

Fraction::Fraction(const Fraction &other) {
  this->num = other.getNum();
  this->denom = other.getDenom();
}

Fraction operator+(const Fraction & a, const Fraction & b) {
  Fraction sum(b.getDenom()*a.getNum() + a.getDenom()*b.getNum(), 
               b.getDenom()*a.getDenom());
  return sum;
}

Fraction operator-(const Fraction & a, const Fraction & b) {
  Fraction diff(b.getDenom()*a.getNum() - a.getDenom()*b.getNum(), 
               b.getDenom()*a.getDenom());
  return diff;
}

Fraction Fraction::operator-=(const Fraction &b) {
  *this = *this - b;
  return *this;
}

Fraction Fraction::operator+=(const Fraction &b) {
  *this = *this + b;
  return *this;
}

Fraction operator*(int c, Fraction &a) {
  Fraction product(c*a.getNum(), a.getDenom());
  return product;
}

Fraction Fraction::operator*=(int b) {
  *this = b * (*this);
  return *this;
}

Fraction operator*(Fraction &a, Fraction &b) {
  Fraction product(a.getNum()*b.getNum(), b.getDenom()*a.getDenom());
  product.simplify;
  return product;
}

Fraction operator/(Fraction &a, Fraction &b) {
  Fraction quotient(a.getNum()*b.getDenom(), a.getDenom()*b.getNum());
  quotient.simplify();
  return quotient;
}

bool operator==(const Fraction &a, const Fraction &b) {
  if (a.getNum() == b.getNum() &&
      a.getDenom() == b.getDenom()) {
        return true;
      }
  else {
    return false;
  }
}

bool operator!=(const Fraction &a, const Fraction &b) {
  if (a == b) return false;
  else return true;
}

bool operator<(const Fraction &a, const Fraction &b) {
  if (a.getNum()*b.getDenom() < b.getNum()*a.getDenom()) return true;
  else return false;
}

bool operator<=(const Fraction &a, const Fraction &b) {
  if (a < b || a == b) return true;
  else return false;
}

bool operator>(const Fraction &a, const Fraction &b) {
  if (a < b) return false;
  else return true;
}

bool operator>=(const Fraction &a, const Fraction &b) {
  if (a > b || a == b) return true;
  else return false;
}

int gcd(int x, int y) {
  // do until the two numbers become equal
	while (x != y)
	{
		// replace larger number by its difference with the smaller number
		if (x > y)
		   x = x - y;
		else
		   y = y - x; 
	}
  //std::cout << "gcd is terminating" << std::endl;
  return x;
}

void Fraction::simplify() {
  if (this->num == 0) {
    this->denom = 1;
    return;
  }
  else if (this->denom == 1) {
    return;
  }
  //std::cout << "simplify" << std::endl;
  int factor = gcd(this->num, this->denom);
  //std::cout << "factor taken" << std::endl;
  this->num /= factor;
  //std::cout << "divide num" << std::endl;
  this->denom /= factor;
  //std::cout << "divide denom" << std::endl;
}

int Fraction::getNum() const {
  return this->num;
}

int Fraction::getDenom() const {
  return this->denom;
}

std::ostream &operator<<(std::ostream &str, const Fraction &a) {
  str << a.getNum() << " / " << a.getDenom() << std::endl;
  return str;
}