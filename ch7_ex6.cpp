#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

typedef unsigned int uint;

//For a prime number, the return value is empty.
inline vector<uint> prime_factors(uint n) {
  vector<uint> f;
  if (n > 2) {
    uint o = n;
    f.reserve(8);
    while (n % 2 == 0) {
      f.push_back(2);
      n /= 2;
    }
    uint p = 3;
    double rt = sqrt(n);
    while (p < rt + 1) {
      if (n % p == 0) {
        f.push_back(p);
        n /= p;
        while (n % p == 0) {
          f.push_back(p);
          n /= p;
        }
        rt = sqrt(n);
      }
      p += 2;
    }
    if (n > 1 && o != n)
      f.push_back(n);
  }
  return f;
}

inline uint sum_of_digits(uint n) {
  uint s = 0;
  while (n) {
    s += n % 10;
    n /= 10;
  }
  return s;
}

inline bool is_smith(uint n) {
  bool r = false;
  vector<uint> f = prime_factors(n);
  if (!f.empty()) {
    uint sf = 0;
    for (uint i = 0; i < f.size(); i++) {
      sf += sum_of_digits(f[i]);
    }
    r = sum_of_digits(n) == sf;
  }
  return r;
}

inline uint smith(uint n) {
  uint i = n + 1;
  for (; i < UINT_MAX; i++) {
    if (is_smith(i))
      break;
  }
  return i < INT_MAX ? i : 0;
}

int main() {
  uint t;
  cin >> t;
  for (uint i = 0; i < t; i++) {
    uint n;
    cin >> n;
    cout << smith(n) << endl;
  }
  return 0;
}
