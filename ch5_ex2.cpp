/***********************************************************
 * Reverse and Add
 * PC/UVa IDs: 110502/10018
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>

#define MAX_SIZE 10

using namespace std;

typedef long long llt;

typedef vector<char> BigInt;

ostream & operator <<(ostream & os, const BigInt & n) {
  for (int i = n.size() - 1; i >= 0; i--)
    os << (char)('0' + n[i]);
  return os;
}

inline BigInt to_bigint(llt n) {
  BigInt v;
  if (n) {
    v.reserve(MAX_SIZE);
    while (n) {
      v.push_back(n % 10);
      n /= 10;
    }
  }
  else {
    v.push_back(0);
  }
  return v;
}

inline bool done(const BigInt & bn) {
  bool ok = true;
  int h = bn.size() / 2;
  for (int i = 0; i < h; i++) {
    if (bn[i] != bn[bn.size() - i - 1]) {
      ok = false;
      break;
    }
  }
  return ok;
}

inline void add(BigInt & bn, const BigInt & br) {
  int carry = 0;
  for (int i = 0; i < bn.size(); i++) {
    int s = bn[i] + br[i] + carry;
    if (s > 9) {
      carry = 1;
      s %= 10;
    }
    else {
      carry = 0;
    }
    bn[i] = s;
  }
  if (carry)
    bn.push_back(1);
}

int reverse_add(llt n, BigInt & bn) {
  int c = 0;
  bn = to_bigint(n);
  while (!done(bn)) {
    c++;
    BigInt br(bn.rbegin(), bn.rend());
    add(bn, br);
  }
  return c;
}

int main() {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    llt p;
    cin >> p;
    BigInt bn;
    int t = reverse_add(p, bn);
    cout << t << ' ' << bn << endl;
  }
  return 0;
}
