#include <iostream>
#include <vector>

using namespace std;

void hartal(vector<bool> & days, int h) {
  int n = days.size();
  int t = h - 1;
  while (t < n) {
    int r = t % 7;
    if (r != 5 && r != 6)
      days[t] = true;
    t += h;
  }
}

int main() {
  int t;
  if (cin >> t) {
    for (int i = 0; i < t; i++) {
      int n, p;
      vector<bool> days;
      cin >> n >> p;
      days.resize(n, false);
      for (int j = 0; j < p; j++) {
        int h;
        cin >> h;
        hartal(days, h);
      }
      int count = 0;
      for (int j = 0; j < n; j++) {
        if (days[j])
          count++;
      }
      cout << count << endl;
    }
  }
  return 0;
}