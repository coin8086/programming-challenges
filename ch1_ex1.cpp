/***********************************************************
 * The 3n + 1 Problem
 * PC/UVa IDs: 110101/100
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <vector>
#include <iostream>

#ifdef DEBUG
#include "../comm_headers/debug_helper.h"
#else
#define DEBUG_OUT(...)
#endif

#define MAX 999999

using namespace std;

vector<int> r(MAX + 1);

int length(int i) {
  DEBUG_OUT("\n--------------- length of %d --------------\n", i);

  if (r[i]) {
    DEBUG_OUT("=%d\n", r[i]);
    return r[i];
  }

  typedef long long ll_t;
  vector<ll_t> s(8);
  s[0] = i;
  int j = 0;
  ll_t n = s[j];
  while ((n <= MAX && !r[n]) || n > MAX) {
    if (s.size() == j + 1)
      s.resize(s.size() * 2);

    DEBUG_OUT("%lld ", n);

    if (n % 2)
      s[++j] = 3 * n + 1;
    else
      s[++j] = n / 2;

    n = s[j];
  }

  int l = r[i] = r[n] + j;
  DEBUG_OUT("... \n=%d\n", l);

  for (int k = 1; k < j; k++) {
    ll_t m = s[k];
    if (m < MAX && !r[m])
      r[m] = l - k;
  }
  return l;
}

int main() {
  r[1] = 1;
  int a, b;
  while (cin >> a >> b) {
    int l, r;
    if (a <= b) {
      l = a;
      r = b;
    }
    else {
      l = b;
      r = a;
    }
    int max = 0;
    for (int i = l; i <= r; i++) {
      int len = length(i);
      if (len > max)
        max = len;
    }
    cout << a << ' ' << b << ' ' << max << endl;
  }
  return 0;
}

