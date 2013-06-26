/***********************************************************
 * Primary Arithmetic
 * PC/UVa IDs: 110501/10035
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#define MAX_SIZE 10

using namespace std;

int carry_times(vector<char> & n, vector<char> & m) {
  int carry = 0;
  int times = 0;
  int size = n.size() >= m.size() ? n.size() : m.size();
  n.resize(size);
  m.resize(size);
  for (int i = 0; i < size; i++) {
    int s = carry + n[i] + m[i];
    if (s > 9) {
      carry = 1;
      times++;
    }
    else {
      carry = 0;
    }
  }
  return times;
}

inline vector<char> read_n(istream & is) {
  vector<char> n;
  n.reserve(MAX_SIZE);
  char ch;
  while (is.get(ch) && ch != ' ')
    n.push_back(ch - '0');
  reverse(n.begin(), n.end());
  return n;
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line == "0 0")
      break;
    istringstream is(line);
    vector<char> n = read_n(is);
    vector<char> m = read_n(is);
    int t = carry_times(n, m);
    if (!t)
      cout << "No carry operation.";
    else if (t == 1)
      cout << "1 carry operation.";
    else
      cout << t << " carry operations.";
    cout << endl;
  }
  return 0;
}
