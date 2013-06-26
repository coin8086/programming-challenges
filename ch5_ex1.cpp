/***********************************************************
 * Primary Arithmetic
 * PC/UVa IDs: 110501/10035
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>

#define MAX_SIZE 10

using namespace std;

inline vector<char> to_vec(int n) {
  vector<char> v;
  v.reserve(MAX_SIZE);
  while (n) {
    v.push_back(n % 10);
    n /= 10;
  }
  return v;
}

int carry_times(int n, int m) {
  if (!n || !m)
    return 0;
  vector<char> bn = to_vec(n);
  vector<char> bm = to_vec(m);
  int carry = 0;
  int times = 0;
  int size = n >= m ? bn.size() : bm.size();
  bn.resize(size);
  bm.resize(size);
  for (int i = 0; i < size; i++) {
    int s = carry + bn[i] + bm[i];
    if (s > 9) {
      carry = 1;
      times++;
    }
    else {
      carry = 0;
    }
  }
  return times;
}

int main() {
  int n, m;
  while ((cin >> n >> m) && (n || m)) {
    int t = carry_times(n, m);
    if (!t)
      cout << "No carry operation.";
    else if (t == 1)
      cout << "1 carry operation.";
    else
      cout << t << " carry operations.";
    cout << endl;
  }
  return 0;
}
