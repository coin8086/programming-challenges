#include <iostream>
#include <vector>
#include <cmath>

#define LIMIT 0.00001

using namespace std;

long double SQRT_5 = sqrt((long double)5);
long double BASE = (1 + SQRT_5) / 2;
long double LN_BASE = log(BASE);
long double LN_SQRT_5 = log(SQRT_5);

vector<int> fib;

void init() {
  fib.resize(13);
  fib[0] = 0;
  fib[1] = 1;
  for (int i = 2; i < fib.size(); i++) {
    fib[i] = fib[i - 1] + fib[i - 2];
  }
}

//First 11 fib numbers are: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
//Notice: 0 is a fib number, and there are two 1s!
int small_fibs(int upper) {
  int i;
  if (upper < 1) {
    i = upper == 0 ? 1 : 0;
  }
  else {
    for (i = fib.size() - 1; i >= 0; i--) {
      if (fib[i] <= upper)
        break;
    }
  }
  return i;
}

int big_fibs(long double upper) {
  long double n = (log(upper) + LN_SQRT_5) / LN_BASE;
  long double ni;
  long double nf = modf(n, &ni);
  int i = ni;
  if (nf > 0.5 && 1 - nf < LIMIT) {
    i++;
  }
  return i;
}

int fibs(long double a, long double b) {
  int n = a - 1 > fib.back() ? big_fibs(a - 1) : small_fibs(a - 1);
  int m = b > fib.back() ? big_fibs(b) : small_fibs(b);
  return m - n;
}

int main() {
  init();
  long double a, b;
  while (cin >> a >> b && !(a == 0 && b == 0)) {
    cout << fibs(a, b) << endl;
  }
  return 0;
}
