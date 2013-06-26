/***********************************************************
 * Ones
 * PC/UVa IDs: 110504/10127
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>

using namespace std;

typedef vector<char> BigNumber;

inline BigNumber bignum(int n) {
  BigNumber r;
  while (n) {
    r.push_back(n % 10);
    n /= 10;
  }
  return r;
}

inline void shift_add(BigNumber & n, char d) {
  n.push_back(0);
  for (int i = n.size() - 2; i >= 0; i--) {
    n[i + 1] = n[i];
  }
  n[0] = d;
}

inline bool less_than(const BigNumber & op1, const BigNumber & op2) {
  bool r = false;
  if (op1.size() != op2.size()) {
    r = op1.size() < op2.size();
  }
  else {
    for (int i = op1.size() - 1; i >= 0; i--) {
      if (op1[i] != op2[i]) {
        r = op1[i] < op2[i];
        break;
      }
    }
  }
  return r;
}

inline void subtract(BigNumber & op1, const BigNumber & op2) {
  int borrow = 0;
  int i;
  for (i = 0; i < op2.size(); i++) {
    char d = op1[i] - op2[i] - borrow;
    if (d < 0) {
      d += 10;
      borrow = 1;
    }
    else
      borrow = 0;
    op1[i] = d;
  }
  for (i = op2.size(); i < op1.size(); i++) {
    char d = op1[i] - borrow;
    if (d < 0) {
      d += 10;
      borrow = 1;
    }
    else
      borrow = 0;
    op1[i] = d;
  }
  while (op1.size() && !op1.back())
    op1.pop_back();
}

inline BigNumber first(const BigNumber & n) {
  BigNumber r(n.size(), 1);
  if (n.back() > 1)
    r.push_back(1);
  return r;
}

inline void increase(BigNumber & n) {
  n.push_back(1);
}

bool mod(const BigNumber & op1, const BigNumber & op2) {
  BigNumber r;
  for (int i = op1.size() - 1; i >= 0; i--) {
    shift_add(r, op1[i]);
    while (!less_than(r, op2)) {
      subtract(r, op2);
    }
  }
  return r.size();
}

int length(int n) {
  BigNumber bn = bignum(n);
  BigNumber t = first(bn);
  while (mod(t, bn)) {
    increase(t);
  }
  return t.size();
}

int main() {
  int n;
  while (cin >> n) {
    cout << length(n) << endl;
  }
  return 0;
}
