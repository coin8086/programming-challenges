#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

class BigNumber {
  friend std::ostream & operator <<(std::ostream & os, const BigNumber & n);
  friend std::istream & operator >>(std::istream & is, BigNumber & n);

  friend BigNumber operator +(int n, const BigNumber & bign) {
    return bign + n;
  }

  friend BigNumber operator -(int n, const BigNumber & bign) {
    return BigNumber(n) - bign;
  }

  friend BigNumber operator *(int n, const BigNumber & bign) {
    return bign * n;
  }

  friend BigNumber operator /(int n, const BigNumber & bign) {
    return BigNumber(n) / bign;
  }

public:
  BigNumber() : sign(1) {}

  BigNumber(const BigNumber & n) : digits(n.digits), sign(n.sign) {}

  BigNumber(int n) {
    sign = n < 0 ? -1 : 1;
    if (n) {
      int abs = n < 0 ? n * -1 : n;
      while (abs) {
        digits.push_back(abs % 10);
        abs /= 10;
      }
    }
  }

  BigNumber & operator =(const BigNumber & n) {
    if (&n != this) {
      this->digits = n.digits;
      this->sign = n.sign;
    }
    return *this;
  }

  int compare(const BigNumber & n) const;

  bool operator ==(const BigNumber & n) const {
    return compare(n) == 0 ? true : false;
  }

  bool operator !=(const BigNumber & n) const {
    return !operator ==(n);
  }

  bool operator <(const BigNumber & n) const {
    return compare(n) == -1 ? true : false;
  }

  bool operator <=(const BigNumber & n) const {
    return !operator >(n);
  }

  bool operator >(const BigNumber & n) const {
    return compare(n) == 1 ? true : false;
  }

  bool operator >=(const BigNumber & n) const {
    return !operator <(n);
  }

  BigNumber operator +(const BigNumber & n) const;
  BigNumber operator -(const BigNumber & n) const;
  BigNumber operator *(const BigNumber & n) const;
  BigNumber operator /(const BigNumber & n) const;
  BigNumber & operator +=(const BigNumber & n);
  BigNumber & operator -=(const BigNumber & n);

  bool equal_sign(const BigNumber & n) const {
    return sign == n.sign;
  }

  bool negative() const {
    return sign != 1;
  }

  bool zero() const {
    return !digits.size();
  }

  BigNumber abs() const {
    BigNumber n = *this;
    n.sign = 1;
    return n;
  }

private:
  typedef std::vector<char> Digits;

  void ensure() {  //ensure no negative zero and no padding zeros before
    while (digits.size() && !digits.back())
      digits.pop_back();
    if (!digits.size())
      sign = 1;
  }

  void shift() {
    if (!zero()) {
      digits.push_back(0);
      for (int i = digits.size() - 2; i >= 0; i--) {
        digits[i + 1] = digits[i];
      }
      digits[0] = 0;
    }
  }

  void reset() {
    digits.clear();
    sign = 1;
  }

  static void add(const Digits & op1, const Digits & op2, Digits & result);
  static void subtract(const Digits & op1, const Digits & op2, Digits & result);

private:
  Digits digits;
  char sign;
};

std::ostream & operator <<(std::ostream & os, const BigNumber & n) {
  if (n.zero()) {
    os << 0;
  }
  else {
    if (n.negative())
      os << '-';
    for (int i = n.digits.size() - 1; i >= 0; i--)
      os << (int)n.digits[i];
  }
  return os;
}

std::istream & operator >>(std::istream & is, BigNumber & n) {
  char d;
  while (isspace(d = is.get()));
  if (!isdigit(d) && d != '-' && d != '+') {
    is.setstate(std::ios_base::failbit);
    return is;
  }
  n.reset();
  if (d == '-')
    n.sign = -1;
  else if (isdigit(d))
    n.digits.push_back(d - '0');
  while (isdigit(d = is.get()))
    n.digits.push_back(d - '0');
  is.unget();
  reverse(n.digits.begin(), n.digits.end());
  n.ensure();
  return is;
}

int BigNumber::compare(const BigNumber & n) const {
  int r = 0;
  if (!equal_sign(n)) {
    r = negative() ? -1 : 1;
  }
  else {
    if (digits.size() != n.digits.size()) {
      r = digits.size() < n.digits.size() ? -1 : 1;
    }
    else {
      for (int i = digits.size() - 1; i >= 0; i--) {
        if (digits[i] != n.digits[i]) {
          r = digits[i] < n.digits[i] ? -1 : 1;
          break;
        }
      }
    }
    if (negative())
      r = r * -1;
  }
  return r;
}

void BigNumber::add(const Digits & op1, const Digits & op2, Digits & result) {
  char carry = 0;
  int min = std::min(op1.size(), op2.size());
  const Digits & big = op1.size() > op2.size() ? op1: op2;
  result.resize(big.size());
  int i;
  for (i = 0; i < min; i++) {
    char d = carry + op1[i] + op2[i];
    carry = d > 9 ? 1 : 0;
    result[i] = d % 10;
  }
  for (i = min; i < big.size(); i++) {
    char d = carry + big[i];
    carry = d > 9 ? 1 : 0;
    result[i] = d % 10;
  }
  if (carry)
    result.push_back(carry);
  //result.shrink_to_fit();
}

BigNumber BigNumber::operator +(const BigNumber & n) const {
  BigNumber r;
  if (!equal_sign(n)) {
    r = n.negative() ? *this - n.abs() : n - abs();
  }
  else {
    add(digits, n.digits, r.digits);
    r.sign = sign;
    r.ensure();
  }
  return r;
}

BigNumber & BigNumber::operator +=(const BigNumber & n) {
  if (!equal_sign(n)) {
    if (n.negative())
      *this -= n.abs();
    else {
      sign = 1;
      *this = n - *this;
    }
  }
  else {
    add(digits, n.digits, digits);
    ensure();
  }
  return *this;
}

//op1 must not be less than op2!
void BigNumber::subtract(const Digits & op1, const Digits & op2, Digits & result) {
  char borrow = 0;
  int min = op2.size();
  int i;
  result.resize(op1.size());
  for (i = 0; i < min; i++) {
    char d = op1[i] - op2[i] - borrow;
    if (d < 0) {
      d += 10;
      borrow = 1;
    }
    else {
      borrow = 0;
    }
    result[i] = d;
  }
  for (i = min; i < op1.size(); i++) {
    char d = op1[i] - borrow;
    if (d < 0) {
      d += 10;
      borrow = 1;
    }
    else {
      borrow = 0;
    }
    result[i] = d;
  }
  while (result.size() && !result.back())
    result.pop_back();
  //result.shrink_to_fit();
}

BigNumber BigNumber::operator -(const BigNumber & n) const {
  BigNumber r;
  if (!equal_sign(n)) {
    r = n.negative() ? *this + n.abs() : abs() + n;
    if (negative())
      r.sign = -1;
  }
  else {
    if (negative()) {
      r = n.abs() - abs();
    }
    else {
      int cmp = compare(n);
      if (cmp) {
        const std::vector<char> & big = cmp == -1 ? n.digits : digits;
        const std::vector<char> & small = cmp == -1 ? digits : n.digits;
        subtract(big, small, r.digits);
        r.sign = cmp;
        r.ensure();
      }
    }
  }
  return r;
}

BigNumber & BigNumber::operator -=(const BigNumber & n) {
  if (!equal_sign(n)) {
    if (n.negative())
      *this += n.abs();
    else {
      sign = 1;
      *this += n;
      sign = -1;
    }
  }
  else {
    if (negative()) {
      sign = 1;
      *this = n.abs() - *this;
    }
    else {
      int cmp = compare(n);
      if (cmp) {
        const std::vector<char> & big = cmp == -1 ? n.digits : digits;
        const std::vector<char> & small = cmp == -1 ? digits : n.digits;
        subtract(big, small, digits);
        sign = cmp;
        ensure();
      }
      else {
        digits.clear();
      }
    }
  }
  return *this;
}

BigNumber BigNumber::operator *(const BigNumber & n) const {
  BigNumber r;
  if (!zero() && !n.zero()) {
    BigNumber t = *this;
    for (int i = 0; i < n.digits.size(); i++) {
      if (i)
        t.shift();
      for (int j = 0; j < n.digits[i]; j++)
        r += t;
    }
    r.sign = sign * n.sign;
    r.ensure();
  }
  return r;
}

//TODO: throw exception when divider is zero
BigNumber BigNumber::operator /(const BigNumber & n) const {
  BigNumber q, r;
  BigNumber absn = n.abs();
  q.digits.resize(digits.size());
  for (int i = digits.size() - 1; i >= 0; i--) {
    r.shift();
    r += BigNumber(digits[i]);
    q.digits[i] = 0;
    while (r >= absn) {
      q.digits[i]++;
      r -= absn;
    }
  }
  q.sign = sign * n.sign;
  q.ensure();
  return q;
}

using std::cin;
using std::cout;
using std::endl;

int main() {
  BigNumber op1, op2, r;
  char op;
  while (cin >> op1 >> op >> op2) {
    switch (op) {
      case '+':
        r = op1 + op2;
        break;
      case '-':
        r = op1 - op2;
        break;
      case '*':
        r = op1 * op2;
        break;
      case '/':
        r = op1 / op2;
        break;
    }
    cout << r << endl;
  }
  return 0;
}
