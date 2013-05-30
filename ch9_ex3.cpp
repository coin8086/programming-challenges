#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

typedef vector<vector<pair<int, int> > > Graph;

int trips(const Graph & g, int src, int dest, int t) {
  queue<int> q;
  vector<int> cap(g.size());
  cap[src] = INT_MAX;
  q.push(src);
  while (!q.empty()) {
    int v = q.front();
    int c = cap[v];
    q.pop();
    for (int i = 0; i < g[v].size(); i++) {
      int v2 = g[v][i].first;
      int c2 = g[v][i].second;
      int m = min(c, c2);
      if (cap[v2] < m) {
        cap[v2] = m;
        q.push(v2);
      }
    }
  }
  return ceil(1.0 * t / (cap[dest] - 1));
}

int main() {
  int nv, ne;
  int count = 0;
  while ((cin >> nv >> ne) && nv) {
    Graph g(nv + 1);
    for (int i = 0; i < ne; i++) {
      int v1, v2, p;
      cin >> v1 >> v2 >> p;
      g[v1].push_back(make_pair(v2, p));
      g[v2].push_back(make_pair(v1, p));
    }
    int s, d, t;
    cin >> s >> d >> t;
    cout << "Scenario #" << ++count << endl;
    cout << "Minimum Number of Trips = " << trips(g, s, d, t) << endl;
    cout << endl;
  }
  return 0;
}
