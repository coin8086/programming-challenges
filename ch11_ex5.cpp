#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int cut(int l, const vector<int> & pos) {
  if (pos.size() < 1)
    return pos.empty() ? 0 : l;
  //n cut positions divides one stick into n + 1 sections.
  //sec stores the beginning position of a section. To make it easy to calculate
  //a section length, sec stores the length of the stick as the begnning of a section
  //beyond the n + 1 real sections.
  vector<int> sec;
  sec.push_back(0);
  sec.insert(sec.end(), pos.begin(), pos.end());
  sec.push_back(l);
  int n = sec.size() - 1;
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
      seg[i][j] = m + (sec[j + 1] - sec[i]); //m + the length of sections from i to j
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
