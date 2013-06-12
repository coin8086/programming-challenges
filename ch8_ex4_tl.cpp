#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef vector<vector<int> > Graph;

int bt(const Graph & g, const vector<bool> & del) {
  int min = INT_MAX;
  for (int i = 0; i < del.size(); i++) {
    if (!del[i]) {
      vector<bool> d = del;
      d[i] = true;
      for (int j = 0; j < g[i].size(); j++) {
        d[g[i][j]] = true;
      }
      int m = bt(g, d);
      if (m < min) {
        min = m;
        if (!min)
          break;
      }
    }
  }
  return min == INT_MAX ? 0 : min + 1;
}

int serv_station(const Graph & g) {
  vector<bool> del(g.size());
  return bt(g, del);
}

int main() {
  int n, m;
  while ((cin >> n >> m) && n && m) {
    Graph g(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--; //we start from 0
      g[u].push_back(v);
      g[v].push_back(u);
    }
    cout << serv_station(g) << endl;
  }
  return 0;
}
