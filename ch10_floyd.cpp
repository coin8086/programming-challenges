#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef vector<vector<int> > Graph;

void init(Graph & g) {
  for (int i = 0; i < g.size(); i++) {
    for (int j = 0; j < g.size(); j++) {
      if (i == j)
        g[i][j] = 0;
      else
        g[i][j] = INT_MAX;
    }
  }
}

void floyd(Graph & g) {
  int n = g.size();
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      int ik = g[i][k];
      if (ik == INT_MAX)
        continue;
      for (int j = 0; j < n; j++) {
        if (g[k][j] == INT_MAX)
          continue;
        g[i][j] = min(g[i][j], ik + g[k][j]);
      }
    }
  }
}

int main(int argc, char ** argv) {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int nv = 0, ne = 0;
    cin >> nv >> ne;
    Graph g(nv, vector<int>(nv));
    init(g);
    for (int j = 0; j < ne; j++) {
      int u, v, w;
      cin >> u >> v >> w;
      g[u][v] = w;
      g[v][u] = w;
    }
    floyd(g);
    for (int i = 0; i < g.size(); i++) {
      for (int j = 0; j < g.size(); j++) {
        cout << (g[i][j] == INT_MAX ? ' ' : g[i][j]) << ' ';
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
