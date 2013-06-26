/***********************************************************
 * Steps
 * PC/UVa IDs: 110608/846
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int values[] = {0, 0, 2, 3};

int steps(int d) {
  int r;
  if (d > 3) {
    int n = floor(sqrt(d));
    long long nn = n * n;
    if (nn == d)
      r = 2 * n - 1;
    else if (d <= nn + n)
      r = 2 * n;
    else
      r = 2 * n + 1;
  }
  else {
    r = values[d];
  }
  return r;
}

int main() {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    cout << steps(y - x) << endl;
  }
  return 0;
}
