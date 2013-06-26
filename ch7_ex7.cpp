/***********************************************************
 * Marbles
 * PC/UVa IDs: 110707/10090
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned int uint;
typedef long long llt;
typedef long double ldt;

uint gcd(uint n1, uint n2, llt & i1, llt & i2) {
  uint d;
  if (n1 < n2) {
    d = gcd(n2, n1, i2, i1);
  }
  else if (!n2) {
    i2 = 0;
    i1 = 1;
    d = n1;
  }
  else {
    llt ii1, ii2;
    d = gcd(n2, n1 % n2, ii1, ii2);
    i1 = ii2;
    i2 = ii1 - (n1 / n2) * ii2;
  }
  return d;
}

bool marbles(uint n, uint c1, uint n1, uint c2, uint n2, uint & m1, uint & m2) {
  llt i1, i2;
  uint d = gcd(n1, n2, i1, i2);
  if (n % d)
    return false;
  if (d != 1) {
    n /= d;
    n1 /= d;
    n2 /= d;
  }
  llt low = ceil((ldt)(-1.0) * i1 * n / n2);
  llt high = floor((ldt)n / ((llt)n1 * n2) - (ldt)i1 * n / n2);
  if (low > high)
    return false;
  llt k = (llt)c1 * n2 >= (llt)c2 * n1 ? low : high;
  m1 = k * n2 + i1 * n;
  m2 = (n - n1 * m1) / n2;
  return true;
}

int main() {
  uint n;
  while (cin >> n && n) {
    uint c1, n1, c2, n2;
    cin >> c1 >> n1 >> c2 >> n2;
    uint m1, m2;
    if (marbles(n, c1, n1, c2, n2, m1, m2))
      cout << m1 << ' ' << m2 << endl;
    else
      cout << "failed" << endl;
  }
  return 0;
}
