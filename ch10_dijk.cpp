#include <iostream>
#include <vector>
#include <utility>
#include <climits>

using namespace std;

typedef vector<vector<pair<int, int> > > Graph;

//g must not be empty.
vector<int> dijk(const Graph & g, int s) {
  vector<int> pred(g.size(), -1);
  vector<int> dist(g.size(), INT_MAX);
  vector<bool> in(g.size());  //whether a vertex is already in tree
  int v = s;
  dist[v] = 0;
  while (!in[v]) {
    in[v] = true;
    int i;
    for (i = 0; i < g[v].size(); i++) {
      int w = g[v][i].first;
      int weight = g[v][i].second;
      if (!in[w] && dist[w] > dist[v] + weight) {
        dist[w] = dist[v] + weight;
        pred[w] = v;
      }
    }
    int d = INT_MAX;
    for (i = 0; i < dist.size(); i++) {
      if (!in[i] && dist[i] < d) {
        d = dist[i];
        v = i;
      }
    }
  }
  return dist;
}

int main(int argc, char ** argv) {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int nv = 0, ne = 0;
    cin >> nv >> ne;
    Graph g(nv);
    for (int j = 0; j < ne; j++) {
      int u, v, w;
      cin >> u >> v >> w;
      g[u].push_back(make_pair(v, w));
      g[v].push_back(make_pair(u, w));
    }
    vector<int> dist = dijk(g, 0);
    for (int i = 1; i < dist.size(); i++) {
      cout << dist[i] << endl;
    }
    cout << endl;
  }
  return 0;
}
