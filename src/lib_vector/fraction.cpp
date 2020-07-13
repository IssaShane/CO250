#include "fraction.h"

using namespace std;

Fraction::Fraction() {
  this->num = 0;
  this->denom = 1;
}

Fraction::Fraction(int num, int denom) { 
  this->num = num;
  this->denom = denom;
}

Fraction::Fraction(Fraction n, Fraction d) {
  *this = (n/d);
  if (this->getDenom() == 0) cout << "zero denom" << endl;
  //this->simplify();
}

Fraction::Fraction(int num) {
  this->num = num;
  this->denom = 1;
}

Fraction::Fraction(const Fraction &other) {
  this->num = other.getNum();
  this->denom = other.getDenom();
}

// operator+(a,b) returns the value of the sum of the fractions a and b
// Efficiency: O(1)
Fraction operator+(const Fraction &a, const Fraction & b) {
  Fraction sum(b.getDenom()*a.getNum() + a.getDenom()*b.getNum(), 
               b.getDenom()*a.getDenom());
  return sum;
}

// operator-(a,b) returns the value of the difference of the fractions a and b
// Efficiency: O(1)
Fraction operator-(const Fraction & a, const Fraction & b) {
  Fraction diff(b.getDenom()*a.getNum() - a.getDenom()*b.getNum(), 
               b.getDenom()*a.getDenom());
  return diff;
}

// operator-=(b) subtracts the value of the fraction b from this
// Effects: mutates data
// Efficiency: O(1)
// Requires: this is an lvalue
Fraction & Fraction::operator-=(const Fraction &b) {
  *this = *this - b;
  return *this;
}

// operator+=(b) adds the value of the fraction b to this
// Effects: mutates data
// Efficiency: O(1)
// Requires: this is an lvalue
Fraction & Fraction::operator+=(const Fraction &b) {
  *this = *this + b;
  return *this;
}

// operator*(c,a) returns the product of the fraction a and the constant c
// Efficiency: O(1)
Fraction operator*(int c, const Fraction &a) {
  Fraction product(c*a.getNum(), a.getDenom());
  return product;
}

// operator*=(b) multiplies this by the constant b
// Effects: mutates data
// Efficiency: O(1)
// Requires: this is an lvalue
Fraction & Fraction::operator*=(int b) {
  *this = b * (*this);
  return *this;
}

// operator*=(b) multiplies this by the fraction b
// Effects: mutates data
// Efficiency: O(1)
// Requires: this is an lvalue
Fraction & Fraction::operator*=(const Fraction& b) {
  *this = b * (*this);
  return *this;
}

// operator*(a,b) returns the product of the fractions a and b
// Efficiency: O(1)
Fraction operator*(const Fraction &a, const Fraction &b) {
  Fraction product(a.getNum()*b.getNum(), b.getDenom()*a.getDenom());
  if (a == Fraction(0) || b == Fraction(0)) return Fraction(0);
  return product;
}

// operator/(a,b) returns the quotient of the fraction a by the fraction b,
//   and gives an error if attempting to divide by zero
// Effects: outputs to standard output and standard error
// Efficiency: O(n)
Fraction operator/(const Fraction &a, const Fraction &b) {
  Fraction bcheck = b;
  bcheck.simplify();
  if (bcheck == Fraction{0}) {
    cerr << "dividing by 0: a = " << a << " b = " << b << endl;
    cout << "dividing by 0: a = " << a << " b = " << b << endl;
  }
  Fraction quotient(a.getNum()*b.getDenom(), a.getDenom()*b.getNum());
  return quotient;
}

// operator/=(b) divides this by the fraction b
// Effects: mutates data
// Efficiency: O(1)
// Requires: this is an lvalue
Fraction & Fraction::operator/=(const Fraction &b) {
  *this = *this / b;
  return *this;
}

// operator==(a,b) returns true iff a == b, and false otherwise
// Efficiency: O(1)
bool operator==(const Fraction &a, const Fraction &b) {
  Fraction a_ = a;
  Fraction b_ = b;
  a_.simplify();
  b_.simplify();
  if (a_.getNum() == b_.getNum() &&
      a_.getDenom() == b_.getDenom()) {
        return true;
      }
  else {
    return false;
  }
}

// operator!=(a,b) returns true iff a!=b, and false otherwise
// Efficiency: O(1)
bool operator!=(const Fraction &a, const Fraction &b) {
  if (a == b) return false;
  else return true;
}

// operator<(a,b) returns true iff the fraction a is of lesser value to the 
//   fraction b
// Efficiency: O(1)
bool operator<(const Fraction &a, const Fraction &b) {
  if ((a.getNum()*b.getDenom()) < (b.getNum()*a.getDenom())) return true;
  else return false;
}

// operator<=(a,b) returns true iff the fraction a is of lesser or equal
//   value to the fraction b
// Efficiency: O(1)
bool operator<=(const Fraction &a, const Fraction &b) {
  if (a < b || a == b) return true;
  else return false;
}

// operator>(a,b) returns true iff the fraction a is of greater value than
//   the fraction b
// Efficiency: O(1)
bool operator>(const Fraction &a, const Fraction &b) {
  if (a < b || a == b) return false;
  else return true;
}

// operator>=(a,b) returns true iff the fraction a is of greater or equal 
//   value to the fraction b
// Efficiency: O(1)
bool operator>=(const Fraction &a, const Fraction &b) {
  if (a > b || a == b) return true;
  else return false;
}

// gcx(x,y) finds the greatest common denominator between x and y
// Efficiency: O(n)
// Requires: x,y != 0
int gcd(int x, int y) {
  // do until the two numbers become equal
	while (x != y)
	{
    //cout << "gcd" << endl;
		// replace larger number by its difference with the smaller number
		if (x > y)
		   x = x - y;
		else
		   y = y - x; 
	}
  return x;
}

// simplify() reduces this to its most simplified fractional form
// Effects: mutates data
// Efficiency: O(n)
// Requires: this does not have a denominator of zero
void Fraction::simplify() {
  if (this->num == 0) {
    this->denom = 1;
    return;
  }
  else if (this->denom == 1) {
    return;
  }
  else if (this->num == this->denom) {
    this->num = 1;
    this->denom = 1;
    return;
  }

  if (this->denom < 0) {
    this->denom*=(-1);
    this->num*=(-1);
  }

  if (this->num < 0) {
    this->num *= (-1);
    int factor = gcd(this->num, this->denom);
    if (factor == 0) return;
    this->num /= factor;
    this->denom /= factor;
    this->num *= (-1);
  }
  else {
    int factor = gcd(this->num, this->denom);
    if (factor == 0) return;
    this->num /= factor;
    this->denom /= factor;
  }
  if (this->denom < 0) {
    this->denom*=(-1);
    this->num*=(-1);
  }
}

int Fraction::getNum() const {
  return this->num;
}

int Fraction::getDenom() const {
  return this->denom;
}

// operator<<(str,a) outputs the value of this to the stream str in the form
//   [numerator]/[denominator]
// Effects: outputs to str
// Efficiency: O(1)
// Requires: this is an lvalue
std::ostream &operator<<(std::ostream &str, const Fraction &a) {
  if (a.getDenom() == 1) str << a.getNum();
  else str << a.getNum() << "/" << a.getDenom();
  return str;
}

// operator>>(str,a) takes the value of a fraction from str, and stores it in a
// Effects: mutates a
// Efficiency: O(n)
// Requires: a is an lvalue
istream &operator>>(istream &str, Fraction &a) {
  int num, denom;
  char c;
  cin >> num;
  cin >> c;
  if (c != '/') {
    str.putback(c);
    a = Fraction{num};
    return str;
  }
  cin >> denom;
  a = Fraction{num,denom};
  return str;
}


Fraction abs(const Fraction &x) {
  if (x < 0) return (-1)*x;
  else return x;
}