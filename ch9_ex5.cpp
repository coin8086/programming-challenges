/***********************************************************
 * Edit Step Ladders
 * PC/UVa IDs: 110905/10029
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

typedef vector<string> Dict;
typedef map<string, int> LadderLen;

//p1 and p2 must have the same length.
inline bool equal(const char * p1, const char * p2) {
  for (; *p1 && *p1 == *p2; p1++, p2++);
  return !*p1;
}

//w1 and w2 must be different and not empty!
bool one_step(const string & w1, const string & w2) {
  bool r = false;
  int d = w1.size() - w2.size();
  const char * p1 = w1.c_str();
  const char * p2 = w2.c_str();
  if (!d) {
    while (*p1++ == *p2++);
    if (!*p1)
      r = true;
    else
      r = equal(p1, p2);
  }
  else {
    while (*p1++ == *p2++);
    if (d > 0)
      r = equal(p1, --p2);
    else
      r = equal(p2, --p1);
  }
#ifdef DEBUG
  cerr << w1 << " and " << w2 << (r ? " is one step" : " is not one step") << endl;
#endif
  return r;
}

inline void search(const string & w, const Dict & d, LadderLen & len, int & max) {
  for (int j = 0; j < d.size(); j++) {
    const string & w2 = d[j];
    if (one_step(w, w2) && len[w2] > max) {
      max = len[w2];
    }
  }
}

int ladder(const Dict & d) {
  LadderLen len;
  vector<Dict> d2(17);
  int r = 0;
  for (int i = d.size() - 1; i > 0; i--) {
    const string & w = d[i];
    int max = -1;
    search(w, d2[w.size()], len, max);
    if (w.size() < 16)
      search(w, d2[w.size() + 1], len, max);
    if (w.size() > 1)
      search(w, d2[w.size() - 1], len, max);
    d2[w.size()].push_back(w);
    len[w] = ++max;
    if (max > r)
      r = max;
  }
  return r + 1;
}

int main() {
  Dict d(1); //The first word is just a place holder
  string w;
  while (cin >> w) {
    d.push_back(w);
  }
  cout << ladder(d) << endl;
  return 0;
}
