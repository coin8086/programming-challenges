#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef vector<string> Dict;

//p1 and p2 must have the same length.
inline bool equal(const char * p1, const char * p2) {
  for (; *p1 && *p1 == *p2; p1++, p2++);
  return !*p1;
}

//w1 and w2 must be different and not empty!
bool one_step(const string & w1, const string & w2) {
  bool r = false;
  int d = w1.size() - w2.size();
  if (abs(d) <= 1) {
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
  }
#ifdef DEBUG
  cerr << w1 << " and " << w2 << (r ? " is one step" : " is not one step") << endl;
#endif
  return r;
}

int ladder(const Dict & d) {
  vector<int> len(d.size());
  int r = 0;
  for (int i = d.size() - 1; i > 0; i--) {
    string w = d[i];
    int max = -1;
    for (int j = i + 1; j < d.size(); j++) {
      if (one_step(w, d[j]) && len[j] > max) {
        max = len[j];
      }
    }
    len[i] = ++max;
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
