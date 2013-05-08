#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> flip(vector<int> & flaps) {
  vector<int> flips;
  vector<int>::iterator begin = flaps.begin();
  vector<int>::iterator end = flaps.end();
  for (int i = 0; i < flaps.size(); i++) {
    vector<int>::iterator icurrent = begin + i;
    vector<int>::iterator imax = max_element(icurrent, end);
    if (imax != icurrent) {
      if (imax + 1 != end) {
        flips.push_back(imax - begin + 1);
        reverse(imax, end);
      }
      flips.push_back(i + 1);
      reverse(icurrent, end);
    }
  }
  flips.push_back(0);
  return flips;
}

int main() {
  string line;
  while (getline(cin, line)) {
    istringstream is(line);
    vector<int> flaps;
    int d;
    while (is >> d) {
      flaps.push_back(d);
    }
    reverse(flaps.begin(), flaps.end());
    vector<int> flips = flip(flaps);
    cout << line << endl;
    for (int i = 0; i < flips.size(); i++) {
      if (i != 0)
        cout << ' ';
      cout << flips[i];
    }
    cout << endl;
  }
}