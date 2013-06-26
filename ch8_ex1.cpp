/***********************************************************
 * Little Bishops
 * PC/UVa IDs: 110801/861
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef unsigned long long ull_t;
typedef vector<pair<int, int> > PVec;

class Black {
public:
  static int rows(int n) {
    return n;
  }

  static int cols(int n) {
    return n % 2 ? n : n - 1;
  }

  static void col_range(int n, int row, int & first, int & last) {
    int mid = cols(n) / 2;
    if (row > mid)
      row = n - 1 - row;
    first = mid - row;
    last = mid + row;
  }

  //1, 1, 2, 3, 4, 5, 6, 7
  static int max(int n) {
    return n > 1 ? n - 1 : 1;
  }
};

class White {
public:
  static int rows(int n) {
    return n - 1;
  }

  static int cols(int n) {
    return n % 2 ? n - 1 : n;
  }

  static void col_range(int n, int row, int & first, int & last) {
    int mid = cols(n) / 2;
    if (row >= mid)
      row = n - 2 - row;
    first = mid - 1 - row;
    last = mid + row;
  }

  //0, 1, 2, 3, 4, 5, 6, 7
  static int max(int n) {
    return n > 1 ? n - 1 : 0;
  }
};

inline bool avail(int col, const PVec & a) {
  for (int i = 0; i < a.size(); i++) {
    if (a[i].second == col)
      return false;
  }
  return true;
}

template<typename T>
void backtrack(int n, int k, PVec & a, int & c) {
  if (a.size() == k) {
    c++;
  }
  //go on only when there are available rows to hold remaining bishops(one in each row)
  else if (k - a.size() <= T::rows(n) - (a.empty() ? 0 : (a.back().first + 1))) {
    int i = a.empty() ? 0 : a.back().first + 1;
    for (; i < T::rows(n); i++) {
      int first, last;
      T::col_range(n, i, first, last);
      for (int j = first; j <= last; j++) {
        if (avail(j, a)) {
          a.push_back(make_pair(i, j));
          backtrack<T>(n, k, a, c);
          a.pop_back();
        }
      }
    }
  }
}

template<typename T>
inline int methods(int n, int k) {
  if (!k)
    return 1;
  int c = 0;
  PVec a;
  backtrack<T>(n, k, a, c);
  return c;
}

ull_t bishops(int n, int k) {
  ull_t c = 0;
  for (int i = 0; i <= k; i++) {
    if (i <= Black::max(n) && k - i <= White::max(n)) {
      ull_t r = methods<Black>(n, i);
      r *= methods<White>(n, k - i);
      c += r;
    }
  }
  return c;
}

int main() {
  int n, k;
  while ((cin >> n >> k) && n) {
    cout << bishops(n, k) << endl;
  }
  return 0;
}
