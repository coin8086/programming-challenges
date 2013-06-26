/***********************************************************
 * How Many Fibs?
 * PC/UVa IDs: 110601/10183
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include "bigint.h"

using namespace std;

vector<BigInt> fib;

void init() {
  fib.reserve(501);
  fib.push_back(0);
  fib.push_back(1);
  fib.push_back(2);
  for (int i = 0; i < 498; i++) {
    int l = fib.size() - 1;
    fib.push_back(fib[l] + fib[l - 1]);
  }
}

int bsearch(const BigInt & v, int s/* start */, int e/* end */) {
  int i;
  int mid = (s + e) / 2;
  int r = v.compare(fib[mid]);
  if (!r) {
    i = mid;
  }
  else if (r < 0) {
    if (s == mid)
      i = s - 1;
    else
      i = bsearch(v, s, mid);
  }
  else {
    if (e == mid + 1)
      i = mid;
    else
      i = bsearch(v, mid + 1, e);
  }
  return i;
}

inline int fibs(const BigInt & a) {
  return a.zero() ? 0 : bsearch(a, 0, fib.size());
}

inline int fibs(const BigInt & a, const BigInt & b) {
  return a.zero() ? fibs(b) : fibs(b) - fibs(a - 1);
}

int main() {
  init();
  BigInt a, b;
  while (cin >> a >> b && !(a.zero() && b.zero())) {
    cout << fibs(a, b) << endl;
  }
  return 0;
}
