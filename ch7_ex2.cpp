/***********************************************************
 * Carmichael Numbers
 * PC/UVa IDs: 110702/10006
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned int uint;

/*
bool prime(uint n) {
  if (n % 2 == 0)
    return false;
  uint i = 3;
  uint h = sqrt(n) + 1;
  while (i <= h) {
    if (n % i == 0)
      return false;
    i += 2;
  }
  return true;
}

uint mod(uint a, uint n, uint m) {
  if (n == 1)
    return a;
  uint x = mod(a, n / 2, m);
  x = (x * x) % m;
  if (n % 2)
    x = (x * a) % m;
  return x;
}

bool carm(uint n) {
  bool r = true;
  for (int i = 2; i < n; i++) {
    if (mod(i, n, n) != i) {
      r = false;
      break;
    }
  }
  if (r && prime(n))
    r = false;
  return r;
}
*/

uint values[] = {
  561,
  1105,
  1729,
  2465,
  2821,
  6601,
  8911,
  10585,
  15841,
  29341,
  41041,
  46657,
  52633,
  62745,
  63973
};

bool carm(uint n) {
  for (int i = 0; i < sizeof(values) / sizeof(uint); i++) {
    if (values[i] == n)
      return true;
  }
  return false;
}

int main() {
  uint n;
  while (cin >> n && n) {
    if (carm(n))
      cout << "The number " << n << " is a Carmichael number." << endl;
    else
      cout << n << " is normal." << endl;
  }
  return 0;
}
