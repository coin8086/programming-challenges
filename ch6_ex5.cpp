#include <iostream>
#include <vector>
#include <cstring>

//////////////////////////////////////////////////////////////
//
// BigInt
//
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

#include <algorithm>
#include <cctype>
#include <cassert>
//#include "bigint.h"

BigInt::BigInt(int n) {
  _sign = n < 0 ? -1 : 1;
  if (n) {
    int abs = n < 0 ? n * -1 : n;
    while (abs) {
      _digits.push_back(abs % 10);
      abs /= 10;
    }
  }
}

std::ostream & operator <<(std::ostream & os, const BigInt & n) {
  if (n.zero()) {
    os << '0';
  }
  else {
    if (n.negative())
      os << '-';
    for (int i = n._digits.size() - 1; i >= 0; i--)
      os << (char)('0' + n._digits[i]);
  }
  return os;
}

std::istream & operator >>(std::istream & is, BigInt & n) {
  char d;
  while (isspace(d = is.get()));
  if (!isdigit(d) && d != '-' && d != '+') {
    is.setstate(std::ios_base::failbit);
    return is;
  }
  n.reset();
  if (d == '-')
    n._sign = -1;
  else if (isdigit(d))
    n._digits.push_back(d - '0');
  while (isdigit(d = is.get()))
    n._digits.push_back(d - '0');
  is.unget();
  std::reverse(n._digits.begin(), n._digits.end());
  n.ensure();
  return is;
}

int BigInt::compare(const BigInt & n) const {
  int r = 0;
  if (!equal_sign(n)) {
    r = negative() ? -1 : 1;
  }
  else {
    if (_digits.size() != n._digits.size()) {
      r = _digits.size() < n._digits.size() ? -1 : 1;
    }
    else {
      for (int i = _digits.size() - 1; i >= 0; i--) {
        if (_digits[i] != n._digits[i]) {
          r = _digits[i] < n._digits[i] ? -1 : 1;
          break;
        }
      }
    }
    if (negative())
      r = r * -1;
  }
  return r;
}

void BigInt::add(const Digits & op1, const Digits & op2, Digits & result) {
  char carry = 0;
  int min = op1.size() < op2.size() ? op1.size() : op2.size();
  const Digits & big = op1.size() > op2.size() ? op1 : op2;
  result.resize(big.size());
  int i;
  for (i = 0; i < min; i++) {
    result[i] = add(op1[i], op2[i], carry);
  }
  for (i = min; i < big.size(); i++) {
    result[i] = add(big[i], 0, carry);
  }
  if (carry)
    result.push_back(carry);
  //result.shrink_to_fit();
}

BigInt BigInt::operator +(const BigInt & n) const {
  BigInt r;
  if (!equal_sign(n)) {
    r = n.negative() ? *this - n.abs() : n - abs();
  }
  else {
    add(_digits, n._digits, r._digits);
    r._sign = _sign;
    r.ensure();
  }
  return r;
}

BigInt & BigInt::operator +=(const BigInt & n) {
  if (!equal_sign(n)) {
    if (n.negative())
      *this -= n.abs();
    else {
      _sign = 1;
      *this = n - *this;
    }
  }
  else {
    add(_digits, n._digits, _digits);
    ensure();
  }
  return *this;
}

//op1 must not be less than op2!
void BigInt::sub(const Digits & op1, const Digits & op2, Digits & result) {
  char borrow = 0;
  int min = op2.size();
  int i;
  result.resize(op1.size());
  for (i = 0; i < min; i++) {
    result[i] = sub(op1[i], op2[i], borrow);
  }
  for (i = min; i < op1.size(); i++) {
    result[i] = sub(op1[i], 0, borrow);
  }
  while (result.size() && !result.back())
    result.pop_back();
  //result.shrink_to_fit();
}

BigInt BigInt::operator -(const BigInt & n) const {
  BigInt r;
  if (!equal_sign(n)) {
    r = n.negative() ? *this + n.abs() : abs() + n;
    if (negative())
      r._sign = -1;
  }
  else {
    if (negative()) {
      r = n.abs() - abs();
    }
    else {
      int cmp = compare(n);
      if (cmp) {
        const std::vector<char> & big = cmp == -1 ? n._digits : _digits;
        const std::vector<char> & small = cmp == -1 ? _digits : n._digits;
        sub(big, small, r._digits);
        r._sign = cmp;
        r.ensure();
      }
    }
  }
  return r;
}

BigInt & BigInt::operator -=(const BigInt & n) {
  if (!equal_sign(n)) {
    if (n.negative())
      *this += n.abs();
    else {
      _sign = 1;
      *this += n;
      _sign = -1;
    }
  }
  else {
    if (negative()) {
      _sign = 1;
      *this = n.abs() - *this;
    }
    else {
      int cmp = compare(n);
      if (cmp) {
        const std::vector<char> & big = cmp == -1 ? n._digits : _digits;
        const std::vector<char> & small = cmp == -1 ? _digits : n._digits;
        sub(big, small, _digits);
        _sign = cmp;
        ensure();
      }
      else {
        _digits.clear();
      }
    }
  }
  return *this;
}

BigInt BigInt::operator *(const BigInt & n) const {
  BigInt r;
  if (!zero() && !n.zero()) {
    BigInt t = *this;
    for (int i = 0; i < n._digits.size(); i++) {
      if (i)
        t.shift_add(0);
      for (int j = 0; j < n._digits[i]; j++)
        r += t;
    }
    r._sign = _sign * n._sign;
    r.ensure();
  }
  return r;
}

//TODO: throw exception when divider is zero
BigInt BigInt::operator /(const BigInt & n) const {
  BigInt q, r;
  BigInt absn = n.abs();
  q._digits.resize(_digits.size());
  for (int i = _digits.size() - 1; i >= 0; i--) {
    r.shift_add(_digits[i]);
    q._digits[i] = 0;
    while (r >= absn) {
      q._digits[i]++;
      r -= absn;
    }
  }
  q._sign = _sign * n._sign;
  q.ensure();
  return q;
}

BigInt BigInt::pow(const BigInt & base, unsigned int n) {
  BigInt r;
  if (!n) {
    r.shift_add(1);
  }
  else if (n == 1) {
    r = base;
  }
  else {
    BigInt h = pow(base, n / 2);
    r = h * h;
    if (n % 2)
      r = r * base;
  }
  return r;
}

static std::vector<BigInt> facts;

BigInt BigInt::fact(unsigned int n) {
  BigInt r;
  if (n + 1 > facts.size()) {
    unsigned int i;
    for (i = facts.size(); i <= n; i++) {
      if (!i) {
        r.shift_add(1);
      }
      else {
        r = facts.back() * i;
      }
      facts.push_back(r);
    }
  }
  else {
    r = facts[n];
  }
  return r;
}

//
// BigInt
//
/////////////////////////////////////////////////////////////////

using namespace std;

BigInt results[22][22];

int m[22][22];

void init() {
  int k, d;
  for (d = 0; d < 22; d++) {
    results[1][d] = 1;
  }
  for (k = 2; k < 22; k++) {
    results[k][0] = 1;
  }
  memset(m, 0, sizeof(m));
}

int compute_m(int k, int d) {
  int r = m[k][d];
  if (!r && d) {
    r = k * compute_m(k, d - 1) + 1;
    m[k][d] = r;
  }
  return r;
}

BigInt compute(int k, int d) {
  BigInt r = results[k][d];
  if (r.zero()) {
    BigInt smaller = compute(k, d - 1);
    int m = compute_m(k, d);
    //x = (k * m)! / ((m!) ^ k);
    //r = (smaller ^ k) * x;
    BigInt x = BigInt::fact(m * k) / BigInt::pow(BigInt::fact(m), k);
    r = BigInt::pow(smaller, k) * x;
    results[k][d] = r;
  }
  return r;
}

int main() {
  init();
  int k, d;
  while (cin >> k >> d) {
    cout << compute(k, d) << endl;
  }
  return 0;
}
