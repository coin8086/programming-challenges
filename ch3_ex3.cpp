/***********************************************************
 * Common Permutation
 * PC/UVa IDs: 110303/10252
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <string>
#include <algorithm>

#define MAX_LEN 1000

using namespace std;

typedef string::iterator It;

string cp(string & s1, string & s2) {
  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());
  string c;
  c.reserve(MAX_LEN);
  It p1 = s1.begin();
  It p2 = s2.begin();
  while (p1 != s1.end() && p2 != s2.end()) {
    if (*p1 == *p2) {
      c += *p1;
      ++p1;
      ++p2;
    }
    else if (*p1 < *p2) {
      ++p1;
    }
    else {
      ++p2;
    }
  }
  return c;
}

int main() {
  string s1, s2;
  s1.reserve(MAX_LEN);
  s2.reserve(MAX_LEN);
  while (getline(cin, s1) && getline(cin, s2)) {
    cout << cp(s1, s2) << endl;
  }
  return 0;
}
