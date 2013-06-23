#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

typedef unsigned int uint;
typedef vector<pair<uint, uint> > PVec;

PVec prime_factors(uint m) {
  PVec r;
  if (m > 2) {
    uint o = m;
    uint i = 2;
    uint c = 0;
    while (m % i == 0) {
      m /= i;
      c++;
    }
    if (c)
      r.push_back(make_pair(i, c));
    i = 3;
    while (i <= sqrt(m) + 1) {
      c = 0;
      while (m % i == 0) {
        m /= i;
        c++;
      }
      if (c)
        r.push_back(make_pair(i, c));
      i += 2;
    }
    if (m > 1 && m != o)
      r.push_back(make_pair(m, 1));
  }
  return r;
}

bool divisible(uint n, uint m) {
  if (m < 2) {
    return m ? true : false;
  }
  bool r = true;
  PVec factors = prime_factors(m);
  if (factors.empty()) {
    if (n < m)
      r = false;
  }
  else {
    for (int i = 0; i < factors.size(); i++) {
      uint p = factors[i].first;
      uint c = factors[i].second;
      uint count = 0;
      uint np;
      uint t = n;
      while ((np = t / p) > 0) {
        count += np;
        if (count >= c)
          break;
        t = np;
      }
      if (count < c) {
        r = false;
        break;
      }
    }
  }
  return r;
}

int main() {
  uint n, m;
  while (cin >> n >> m) {
    if (divisible(n, m)) {
      cout << m << " divides " << n << "!" << endl;
    }
    else {
      cout << m << " does not divide " << n << "!" << endl;
    }
  }
  return 0;
}
