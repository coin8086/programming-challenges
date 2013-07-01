/***********************************************************
 * Distinct Subsequences
 * PC/UVa IDs: 111102/10069
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "bigint.h"

using namespace std;

BigInt times(const string & x, const string & z) {
  if (x.empty() || z.empty() || x.size() < z.size()) {
    return BigInt();
  }
  int rows = x.size() + 1;
  int cols = z.size() + 1;
  vector<vector<BigInt> > T(rows, vector<BigInt>(cols));
  int i, j;
  int c = 0;
  char ch = z[0];
  for (i = 0; i < x.size(); i++) {
    if (x[i] == ch)
      c++;
    T[i + 1][1] = c;
  }
  for (i = 2; i < rows; i++) {
    for (j = 2; j < cols && j <= i; j++) {
      BigInt s = T[i - 1][j];
      if (z[j - 1] == x[i - 1]) {
        s += T[i - 1][j - 1];
      }
      T[i][j] = s;
    }
  }
  return T[x.size()][z.size()];
}

int main() {
  int N = 0;
  cin >> N;
  cin.ignore();
  for (int i = 0; i < N; i++) {
    string x, z;
    cin >> x >> z;
    cout << times(x, z) << endl;
  }
  return 0;
}
