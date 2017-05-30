/***********************************************************
 * Chopsticks
 * PC/UVa IDs: 111107/10271
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <climits>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solve(const vector<int> & l, int k) {
  int n = l.size();
  int p = k + 8;
  vector<vector<int> > m(n);
  for (int i = 0; i < n; i++) {
    m[i].resize(p + 1, INT_MAX);
    m[i][0] = 0;
  }

  vector<int> delta(n - 1);
  for (int i = 0; i < n - 1; i++) {
    int d = l[i + 1] - l[i];
    delta[i] = d * d;
  }

  for (int i = n - 3; i >= 0; i--) {
    for (int j = 1; j <= p; j++) {
      if (i + 3 * j <= n) {
        m[i][j] = min(delta[i] + m[i + 2][j - 1], m[i + 1][j]);
      }
    }
  }

  return m[0][p];
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int k, n;
    cin >> k >> n;
    vector<int> L;
    for (int j = 0; j < n; j++) {
      int l;
      cin >> l;
      L.push_back(l);
    }
    cout << solve(L, k) << endl;
  }
  return 0;
}
