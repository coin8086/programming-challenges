#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <cstdlib>

using namespace std;

typedef vector<vector<pair<int, int> > > Graph;

int sum(const Graph & g, const vector<int> & pred) {
  int s = 0;
  for (int i = 1; i < pred.size(); i++) {
    int w = 0;
    for (int j = 0; j < g[i].size(); j++) {
      if (g[i][j].first == pred[i]) {
        w = g[i][j].second;
        break;
      }
    }
    s += w;
  }
  return s;
}

//g must not be empty.
int prim(const Graph & g) {
  vector<int> pred(g.size(), -1);
  vector<int> dist(g.size(), INT_MAX);
  vector<bool> in(g.size());  //whether a vertex is already in tree
  //dist[0] = 0;
  int v = 0;
  while (!in[v]) {
    in[v] = true;
    int i;
    for (i = 0; i < g[v].size(); i++) {
      int w = g[v][i].first;
      int weight = g[v][i].second;
      if (!in[w] && dist[w] > weight) {
        dist[w] = weight;
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
  return sum(g, pred);
}

class Distance {
public:
  Distance() : v(-1), pd(0) {}

  Distance(int av, int * apd) : v(av), pd(apd) {}

  bool operator <(const Distance & d) const {
    return !(*pd < *d.pd);
  }

  int v;
  int * pd;
};

//g must not be empty.
int prim2(const Graph & g) {
  vector<int> pred(g.size(), -1);
  vector<int> dist(g.size(), INT_MAX);
  vector<bool> in(g.size());  //whether a vertex is already in tree
  dist[0] = 0;
  vector<Distance> q;
  int i;
  for (i = 0; i < dist.size(); i++) {
    q.push_back(Distance(i, &dist[i]));
  }
  make_heap(q.begin(), q.end());
  while (!q.empty()) {
    pop_heap(q.begin(), q.end());
    Distance d = q.back();
    q.pop_back();
    int v = d.v;
    in[v] = true;
    bool updated = false;
    for (i = 0; i < g[v].size(); i++) {
      int w = g[v][i].first;
      int weight = g[v][i].second;
      if (!in[w] && dist[w] > weight) {
        dist[w] = weight;
        pred[w] = v;
        updated = true;
        //Update heap here. It's supposed to cost a O(log(n)) time and speed up
        //alg to O(nlog(n)).
      }
    }
    if (updated) {
      //Probably should not make_heap here. Instead, do a light update in above line,
      //for a make_heap costs a O(n(log(n)) time and this will slow down the alg to
      //O(n^2*log(n)), even worse than above prim O(n^2)!
      make_heap(q.begin(), q.end());
    }
  }
  return sum(g, pred);
}

typedef int (* MST)(const Graph & g);
MST mst[] = {prim, prim2};

int main(int argc, char ** argv) {
  MST m;
  if (argc == 1)
    m = mst[0];
  else
    m = mst[(atoi(argv[1]) + 1) % 2];

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
    cout << m(g) << endl;
  }
  return 0;
}
