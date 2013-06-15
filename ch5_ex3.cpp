#include <iostream>
#include <vector>
#include <cmath>

#define MAX_SIZE 10

long double LOG2 = log(2);
long double LOG2_10 = log(10) / LOG2;

using namespace std;

inline vector<char> to_vec(unsigned int n) {
  vector<char> v;
  v.reserve(MAX_SIZE);
  while (n) {
    v.push_back(n % 10);
    n /= 10;
  }
  return v;
}

unsigned int power_of_2(unsigned int n) {
  unsigned int e = 0;
  vector<char> v = to_vec(n);
  int dl = v.back();    //The highest digit.
  int k = 2 * v.size(); //dl * 10 ^ k
  long double log2_dl = log(dl) / LOG2;
  long double log2_dl_plus = log(dl + 1) / LOG2;
  long double k_log2_10 = k * LOG2_10;
  while (true) {
    //(dl + 1) * 10 ^ k > 2 ^ e >= dl * 10 ^ k
    e = ceil(log2_dl + k_log2_10);
    if (e < log2_dl_plus + k_log2_10) {
      //The next digit, dm, if it exists, must satisfy
      //(dm + 1) * 10 ^ (k - 1) > (2 ^ e - (dl * 10 ^ k)) >= dm * 10 ^ (k - 1)
      //And the next next digit repeats this pattern.
      unsigned int s = dl;
      long double m_log2_10 = k_log2_10;
      int i = v.size() - 2;
      for (; i >= 0; i--) {
        s *= 10;
        s += v[i];
        m_log2_10 -= LOG2_10;
        if (e < log(s) / LOG2 + m_log2_10 || e >= log(s + 1) / LOG2 + m_log2_10)
          break;
      }
      if (i < 0)
        break;
    }
    k_log2_10 += LOG2_10;
  }
  return e;
}

int main() {
  unsigned int n;
  while (cin >> n) {
    cout << power_of_2(n) << endl;
  }
  return 0;
}
