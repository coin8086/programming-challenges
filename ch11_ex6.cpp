/***********************************************************
 * Ferry Loading
 * PC/UVa IDs: 111106/10261
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

vector<int> a;

int solve(int left, int right, int i) {
  if (i >= a.size() || (a[i] > left && a[i] > right))
    return 0;
  int l = 0;
  int r = 0;
  if (a[i] <= left)
    l = solve(left - a[i], right, i + 1) + 1;
  if (a[i] <= right)
    r = solve(left, right - a[i], i + 1) + 1;
  return l >= r ? l : r;
}

int solve2(int L) {
  vector<vector<vector<int> > > m(a.size() + 1);
  for (int i = 0; i < m.size(); i++) {
    m[i].resize(L + 1);
    for (int j = 0; j <= L; j++) {
      m[i][j].resize(L + 1);
    }
  }
  for (int i = m.size() - 2; i >= 0; i--) {
    for (int l = 0; l <= L; l++) {
      for (int r = 0; r <= L; r++) {
        int lm = 0;
        int rm = 0;
        if (a[i] <= l)
          lm = m[i + 1][l - a[i]][r] + 1;
        if (a[i] <= r)
          rm = m[i + 1][l][r - a[i]] + 1;
        m[i][l][r] = lm >= rm ? lm : rm;
      }
    }
  }
  return m[0][L][L];
}

vector<bool> solve3(int L) {
  vector<vector<int> > m(a.size() + 1);
  for (int i = 0; i < m.size(); i++) {
    m[i].resize(L + 1);
  }

  vector<vector<bool> > port(a.size() + 1);
  for (int i = 0; i < port.size(); i++) {
    port[i].resize(L + 1);
  }

  int s = 0;
  for (int i = 0; i < a.size(); i++) {
    s += a[i];
  }

  for (int i = m.size() - 2; i >= 0; i--) {
    s -= a[i];
    for (int j = 0; j <= L; j++) {
      int ra = L * 2 - s - j;
      int l = 0;
      int r = 0;
      if (a[i] <= j)
        l = m[i + 1][j - a[i]] + 1;
      if (a[i] <= ra)
        r = m[i + 1][j] + 1;
      m[i][j] = l >= r ? l : r;
      port[i][j] = l >= r;
    }
  }

  vector<bool> ret;
  int i = 0;
  int j = L;
  while (m[i][j] > 0) {
    ret.push_back(port[i][j]);
    if (port[i][j])
      j -= a[i];
    i++;
  }
  assert(m[0][L] == ret.size());
  return ret;
}

int main() {
  int c;
  cin >> c;
  for (int i = 0; i < c; i++) {
    if (i > 0)
      cout << endl;
    int l = 0;
    cin >> l;
    l *= 100;
    a.clear();
    int c;
    while (true) {
      cin >> c;
      if (!c)
        break;
      a.push_back(c);
    }
    //cout << solve(l, l, 0) << endl;
    //cout << solve2(l) << endl;
    vector<bool> res = solve3(l);
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++) {
      if (res[i])
        cout << "port" << endl;
      else
        cout << "starboard" << endl;
    }
  }
  return 0;
}
