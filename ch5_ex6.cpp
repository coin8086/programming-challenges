/***********************************************************
 * Polynomial Coefficients
 * PC/UVa IDs: 110506/10105
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>

#define MAX 12

using namespace std;

vector<int> fact;

inline void init() {
  fact.resize(MAX + 1);
  fact[0] = 1;
  for (int i = 1; i < fact.size(); i++) {
    fact[i] = fact[i - 1] * i;
  }
}

inline int combination(int n, int m) {
  return fact[n] / (fact[n - m] * fact[m]);
}

int coefficient(int n, vector<int> & e) {
  int r;
  if (e.size() == 1) {
    r = 1;
  }
  else if (e.size() == 2) {
    r = combination(n, e[0]);
  }
  else {
    int last = e.back();
    int c = combination(n, last);
    e.pop_back();
    r = coefficient(n - last, e) * c;
  }
  return r;
}

int main() {
  init();
  int n, k;
  while (cin >> n >> k) {
    vector<int> e;
    e.reserve(k);
    for (int i = 0; i < k; i++) {
      int c;
      cin >> c;
      e.push_back(c);
    }
    cout << coefficient(n, e) << endl;
  }
  return 0;
}
