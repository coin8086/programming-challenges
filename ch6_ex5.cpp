#include <iostream>
#include <vector>
#include <cstring>
#include "bigint.h"

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
