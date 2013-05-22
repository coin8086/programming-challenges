#ifndef __BIGINT__
#define __BIGINT__

#include <iostream>
#include <vector>

class BigInt {
  friend std::ostream & operator <<(std::ostream & os, const BigInt & n);
  friend std::istream & operator >>(std::istream & is, BigInt & n);

  friend BigInt operator +(int n, const BigInt & bign) {
    return bign + n;
  }

  friend BigInt operator -(int n, const BigInt & bign) {
    return BigInt(n) - bign;
  }

  friend BigInt operator *(int n, const BigInt & bign) {
    return bign * n;
  }

  friend BigInt operator /(int n, const BigInt & bign) {
    return BigInt(n) / bign;
  }

public:
  BigInt() : _sign(1) {}

  BigInt(const BigInt & n) : _digits(n._digits), _sign(n._sign) {}

  BigInt(int n);

  int to_int() const {
    int r = 0;
    for (int i = _digits.size() - 1; i >= 0; i--) {
      r *= 10;
      r += _digits[i];
    }
    return r * _sign;
  }

  BigInt & operator =(const BigInt & n) {
    if (&n != this) {
      this->_digits = n._digits;
      this->_sign = n._sign;
    }
    return *this;
  }

  int compare(const BigInt & n) const;

  bool operator ==(const BigInt & n) const {
    return compare(n) == 0 ? true : false;
  }

  bool operator !=(const BigInt & n) const {
    return !operator ==(n);
  }

  bool operator <(const BigInt & n) const {
    return compare(n) == -1 ? true : false;
  }

  bool operator <=(const BigInt & n) const {
    return !operator >(n);
  }

  bool operator >(const BigInt & n) const {
    return compare(n) == 1 ? true : false;
  }

  bool operator >=(const BigInt & n) const {
    return !operator <(n);
  }

/*
  operator bool() const {
    return !zero();
  }
*/

  BigInt operator +(const BigInt & n) const;
  BigInt operator -(const BigInt & n) const;
  BigInt operator *(const BigInt & n) const;
  BigInt operator /(const BigInt & n) const;
  BigInt & operator +=(const BigInt & n);
  BigInt & operator -=(const BigInt & n);

  bool equal_sign(const BigInt & n) const {
    return _sign == n._sign;
  }

  bool negative() const {
    return _sign != 1;
  }

  bool zero() const {
    return !_digits.size();
  }

  BigInt abs() const {
    BigInt n(*this);
    n._sign = 1;
    return n;
  }

  static BigInt pow(const BigInt & base, unsigned int n);
  static BigInt fact(unsigned int n);

private:
  typedef std::vector<char> Digits;

  void ensure() {  //ensure no negative zero and no padding zeros before
    while (_digits.size() && !_digits.back())
      _digits.pop_back();
    if (!_digits.size())
      _sign = 1;
  }

  void shift_add(char d) {
    if (!zero() || d) {
      _digits.push_back(0);
      for (int i = _digits.size() - 2; i >= 0; i--) {
        _digits[i + 1] = _digits[i];
      }
      _digits[0] = d;
    }
  }

  void reset() {
    _digits.clear();
    _sign = 1;
  }

  static char add(char d1, char d2, char & carry) {
    char d = carry + d1 + d2;
    carry = d > 9 ? 1 : 0;
    return d % 10;
  }

  static char sub(char d1, char d2, char & borrow) {
    char d = d1 - d2 - borrow;
    if (d < 0) {
      d += 10;
      borrow = 1;
    }
    else {
      borrow = 0;
    }
    return d;
  }

  static void add(const Digits & op1, const Digits & op2, Digits & result);
  static void sub(const Digits & op1, const Digits & op2, Digits & result);

private:
  Digits _digits;
  char _sign; //+1 or -1
};

#endif
