/***********************************************************
 * How Many Pieces of Land?
 * PC/UVa IDs: 110602/10213
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include "bigint.h"

using namespace std;

BigInt combination(const BigInt & n, unsigned int m) {
  BigInt r;
  if (n == m) {
    r = 1;
  }
  else {
    r = n;
    BigInt f = n;
    for (unsigned int i = 1; i < m; i++) {
      f -= 1;
      r = r * f;
    }
    r = r / BigInt::fact(m);
  }
  return r;
}

inline BigInt how_many_pieces(int n) {
  BigInt bn(n);
  return combination(bn, 2) + combination(bn, 4) + 1;
}

int main() {
  int s;
  cin >> s;
  for (int i = 0; i < s; i++) {
    int n;
    cin >> n;
    cout << how_many_pieces(n) << endl;
  }
  return 0;
}
