#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

inline int sum(const vector<int> & rel, int k) {
  int sum = 0;
  for (int i = 0; i < rel.size(); i++) {
    sum += abs(rel[i] - k);
  }
  return sum;
}

int min(vector<int> & rel) {
  if (rel.size() == 1)
    return 0;
  sort(rel.begin(), rel.end());
  int mid = rel.size() / 2;
  return sum(rel, rel[mid]);
}

int main() {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int r = 0;
    cin >> r;
    vector<int> rel(r);
    int j;
    for (j = 0; j < r; j++) {
      cin >> rel[j];
    }
    cout << min(rel) << endl;
  }
}
