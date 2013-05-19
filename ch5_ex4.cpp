#include <iostream>

using namespace std;

char values[10] = {0, 1, 0, 3, 0, 0, 0, 6, 0, 9};

int length(int n) {
  int l;
  if (n > 10) {
    int r = 1;
    l = 1;
    while (r) {
      r = ((10 * r) % n + 1) % n;
      l++;
    }
  }
  else {
    l = values[n];
  }
  return l;
}

int main() {
  int n;
  while (cin >> n) {
    cout << length(n) << endl;
  }
  return 0;
}
