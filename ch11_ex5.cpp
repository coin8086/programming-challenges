#include <iostream>
#include <vector>
#include <climits>

using namespace std;

inline int len(const vector<int> & sec, int i, int j) {
  int r = 0;
  for (; i <= j; i++)
    r += sec[i];
  return r;
}

int cut(int l, const vector<int> & pos) {
  if (pos.size() < 1)
    return pos.empty() ? 0 : l;
  vector<int> sec(pos.size() + 1);
  sec[0] = pos[0];
  sec[sec.size() - 1] = l - pos.back();
  for (int i = 1; i < pos.size(); i++) {
    sec[i] = pos[i] - pos[i - 1];
  }
  int n = sec.size();
  vector<vector<int> > seg(n, vector<int>(n, 0));
  for (int j = 1; j < n; j++) {
    for (int i = j - 1; i >= 0; i--) {
      int s = 0;
      int m = INT_MAX;
      for (int k = 1; k <= j - i; k++) {
        s = seg[i][j - k] + seg[j - k + 1][j];
        if (s < m)
          m = s;
      }
      seg[i][j] = m + len(sec, i, j);
    }
  }
  return seg[0][n - 1];
}

int main() {
  int l;
  while ((cin >> l) && l > 0) {
    int n = 0;
    cin >> n;
    vector<int> pos;
    pos.reserve(n);
    for (int i = 0; i < n; i++) {
      int p;
      cin >> p;
      pos.push_back(p);
    }
    cout << "The minimum cutting is " << cut(l, pos) << "." << endl;
  }
  return 0;
}
