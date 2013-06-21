#include <iostream>
#include <vector>
#include "bigint.h"

using namespace std;

vector<BigInt> H;
vector<BigInt> P2;

void init() {
  H.reserve(10001);
  H.push_back(0);
  H.push_back(1);
  H.push_back(3);
  H.push_back(5);
  P2.reserve(10001);
  P2.push_back(1);
  P2.push_back(2);
  P2.push_back(4);
  P2.push_back(8);
}

inline BigInt p2(int n) {
  if (n >= P2.size()) {
    for (int i = P2.size(); i <= n; i++) {
      P2.push_back(P2.back() * 2);
    }
  }
  return P2[n];
}

inline BigInt h(int n, int k) {
  return H[k] * 2 + p2(n - k) - 1;
}

BigInt h(int n) {
  if (n >= H.size()) {
    for (int i = H.size(); i <= n; i++) {
      BigInt min = h(i, 1);
      //int mk = 1;
      for (int k = 2; k < i; k++) {
        BigInt m = h(i, k);
        if (m < min) {
          min = m;
          //mk = k;
        }
      }
      //clog << "h(" << i << ", " << mk << ") = " << min << endl;
      H.push_back(min);
    }
  }
  return H[n];
}

int main() {
  init();
  int n;
  while (cin >> n) {
    cout << h(n) << endl;
  }
  return 0;
}
