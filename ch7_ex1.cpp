/***********************************************************
 * Light, More Light
 * PC/UVa IDs: 110701/10110
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned int uint;

inline bool light_on(uint n) {
  uint r = floor(sqrt((double)n));
  return r * r == n;
}

int main() {
  uint n = 0;
  while ((cin >> n) && n) {
    cout << (light_on(n) ? "yes" : "no") << endl;
  }
  return 0;
}
