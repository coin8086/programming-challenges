#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

class Turtle {
public:
  Turtle() {}
  Turtle(int aw, int al) : w(aw), l(al) {}
  bool operator <(const Turtle & t) const { return w < t.w; }
  int w; //weight
  int l; //load = measure - weight
};

vector<Turtle> turtles;

int stack_up(set<int> & stacked, int limit = INT_MAX) {
  string sp(stacked.size() * 2, ' ');
  clog << sp << "limit: " << limit << endl;

  int max = 0;
  for (int i = 0; i < turtles.size() && turtles[i].w <= limit; i++) {
    if (!stacked.count(i)) {
      stacked.insert(i);
      const Turtle & t = turtles[i];
      int lim = min(limit - t.w, t.l);

      clog << sp << "select T<" << t.w << ", " << t.l << ">" << endl;

      int size = stack_up(stacked, lim) + 1;
      if (size > max)
        max = size;
      stacked.erase(i);
    }
  }
  return max;
}

int stack_size() {
  set<int> stacked;
  return stack_up(stacked);
}

int main() {
  int w, m;
  while ((cin >> w >> m)) {
    turtles.push_back(Turtle(w, m - w));
  }
  sort(turtles.begin(), turtles.end());
  cout << stack_size();
  return 0;
}
