/***********************************************************
 * Self-describing Sequence
 * PC/UVa IDs: 110607/10049
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>

using namespace std;

vector<int> F;
vector<int> S; //Sum of first n items from F
int k; //Pointer to item in F

inline void init() {
  F.reserve(50000);
  F.push_back(0);
  F.push_back(1);
  F.push_back(2);
  F.push_back(2);
  k = 2;
  S.push_back(0);
  S.push_back(1);
  S.push_back(3);
  S.push_back(5);
}

inline int f(int n) {
  int r;
  if (F.size() > n) {
    r = F[n];
  }
  else {
    while (S.back() < n) {
      //Add f(k) occurences of k to F, and save the sum of first n items
      int c = F[++k];
      int s = S.back();
      for (int i = 0; i < c; i++) {
        F.push_back(k);
        s += k;
        S.push_back(s);
      }
    }
    for (r = S.size() - 1; r >= 0; r--) {
      if (n > S[r - 1] && n <= S[r])
        break;
    }
  }
  return r;
}

int main() {
  init();
  int n;
  while ((cin >> n) && n > 0) {
    cout << f(n) << endl;
  }
  return 0;
}
