/***********************************************************
 * The Tourist Guide
 * PC/UVa IDs: 110903/10099
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

typedef vector<vector<pair<int, int> > > Graph;

int dfs(const Graph & g, int src, int dest, vector<bool> & visited, int cap) {
  if (src == dest)
    return cap;
  int cap2 = 0;
  visited[src] = true;
  for (int i = 0; i < g[src].size(); i++) {
    int v = g[src][i].first;
    if (!visited[v]) {
      int c = dfs(g, v, dest, visited, min(cap, g[src][i].second));
      cap2 = max(cap2, c);
    }
  }
  visited[src] = false;
  return min(cap, cap2);
}

int trips(const Graph & g, int src, int dest, int t) {
  vector<bool> visited(g.size());
  int cap = dfs(g, src, dest, visited, INT_MAX);
  return ceil(1.0 * t / (cap - 1));
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
