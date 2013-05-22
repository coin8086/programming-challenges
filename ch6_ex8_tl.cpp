#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > solution(4);

void init() {
  solution[2] = vector<int>(2, 1);
  solution[3] = vector<int>(3, 1);
}

int steps(int d) {
  int r;
  if (d + 1 > solution.size()) {
    for (int i = solution.size(); i <= d; i++) {
      vector<int> s = solution.back();
      bool found = false;
      for (int j = s.size() - 2; s[j] <= s[j - 1]; j--) {
        if (s[j] == s[j + 1]) {
          s[j]++;
          found = true;
          break;
        }
      }
      if (!found) {
        s.push_back(1);
      }
      solution.push_back(s);
    }
  }
  r = solution[d].size();
  return r;
}

int main() {
  init();
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    cout << steps(y - x) << endl;
  }
  return 0;
}
