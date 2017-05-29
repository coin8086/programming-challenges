/***********************************************************
 * Weights and Measures
 * PC/UVa IDs: 111103/10154
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


int height(const vector<int> & w, const vector<int> & m) {
  vector<bool> used(w.size());
  int h = 0;
  int capacity = INT_MAX;
  for (int i = 0; i < w.size(); i++) {
    int max = -1;
    int max_j = -1;
    for (int j = 0; j < w.size(); j++) {
      if (!used[j] && w[j] <= capacity) {
        int c = min(m[j] - w[j], capacity - w[j]);
        if (max < c) {
          max = c;
          max_j = j;
        }
      }
    }
    if (max < 0)
      return h;
    capacity = max;
    used[max_j] = true;
    h++;
  }
  return h;
}

int main() {
  vector<int> w, m;
  int wi, mi;
  while ((cin >> wi >> mi)) {
    w.push_back(wi);
    m.push_back(mi);
  }
  cout << height(w, m) << endl;
  return 0;
}
