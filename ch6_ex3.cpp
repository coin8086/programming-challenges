/***********************************************************
 * Counting
 * PC/UVa IDs: 110603/10198
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include "bigint.h"

using namespace std;

vector<BigInt> N;

void init() {
  N.reserve(1001);
  N.push_back(0);
  N.push_back(2);
  N.push_back(5);
  N.push_back(13);
}

BigInt count(int n) {
  if (n >= N.size()) {
    for (int i = N.size(); i <= n; i++) {
      BigInt bi = 2 * N[i - 1] + N[i - 2] + N[i - 3];
      N.push_back(bi);
    }
  }
  return N[n];
}

int main() {
  init();
  int n;
  while (cin >> n) {
    cout << count(n) << endl;
  }
  return 0;
}

