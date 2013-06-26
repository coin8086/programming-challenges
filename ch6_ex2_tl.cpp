/***********************************************************
 * How Many Pieces of Land?
 * PC/UVa IDs: 110602/10213
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>

using namespace std;

typedef long long llt;

vector<llt> pieces;

inline void init() {
  pieces.reserve(3000);
  pieces.push_back(1);
  pieces.push_back(1);
  pieces.push_back(2);
}

/*
  D(N, i) is the increased pieces of land by introducing one edge
  from a newly added point to one of the existed N points. i is the
  number of the existed point, ranging in [0, N - 1]. Point 0 is the 
  point that is immediately adjacent to the newly added point. Point
  1 is immediately adjacent to point 0, and point i to point i - 1.
  The last point, N - 1, is also immediately adjacent to the newly 
  added point.
  llt D(int N, int i) {
    return (llt)i * (N - i - 1) + 1;
  }
  S(N, n) is the Sum of D(N, i), taking all i in [0, n].
*/
inline llt S(llt N, llt n) {
  return (N - 1) * (1 + n) * n / 2 - n * (n + 1) * (n * 2 + 1) / 6 + n + 1;
}

void compute(int n) {
  for (int i = pieces.size(); i <= n; i++) {
    llt last = pieces[i - 1];
    llt inc = S(i - 1, i - 2);
    last += inc;
    pieces.push_back(last);
  }
}

inline llt how_many_pieces(int n) {
  if (n >= pieces.size())
    compute(n);
  return pieces[n];
}

int main() {
  init();
  int s;
  cin >> s;
  for (int i = 0; i < s; i++) {
    int n;
    cin >> n;
    cout << how_many_pieces(n) << endl;
  }
  return 0;
}
