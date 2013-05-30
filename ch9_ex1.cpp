#include <iostream>
#include <vector>
#include <queue>

#define RED 1
#define BLACK (-1)

using namespace std;

typedef vector<vector<int> > Graph;

bool bicolorable(const Graph & g) {
  bool r = true;
  vector<int> color(g.size());
  queue<int> q;
  color[0] = RED;
  q.push(0);
  while (!q.empty()) {
    int v = q.front();
    int c = color[v];
    for (int i = 0; i < g[v].size(); i++) {
      int v2 = g[v][i];
      int & c2 = color[v2];
      if (!c2) {
        c2 = c * -1;
        q.push(v2);
      }
      else if (c2 * c != -1) {
        r = false;
        break;
      }
    }
    q.pop();
  }
  return r;
}

int main() {
  int nv = 0;
  while ((cin >> nv) && nv) {
    Graph g(nv);
    int ne = 0;
    cin >> ne;
    for (int i = 0; i < ne; i++) {
      int v1, v2;
      cin >> v1 >> v2;
      g[v1].push_back(v2);
      g[v2].push_back(v1);
    }
    if (bicolorable(g))
      cout << "BICOLORABLE." << endl;
    else
      cout << "NOT BICOLORABLE." << endl;
  }
  return 0;
}
