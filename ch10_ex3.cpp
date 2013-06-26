/***********************************************************
 * Fire Station
 * PC/UVa IDs: 111003/10278
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef vector<vector<int> > Graph;

void init(Graph & g) {
  int n = g.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j)
        g[i][j] = INT_MAX;
      else
        g[i][j] = 0;
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

inline void merge(vector<int> & v1, const vector<int> & v2) {
  for (int i = 0; i < v1.size(); i++) {
    v1[i] = min(v1[i], v2[i]);
  }
}

int station(Graph & g, const vector<int> & f) {
  floyd(g);
  vector<int> dist = g[f[0]]; //current nearest fire station distance vector.
  int i;
  for (i = 1; i < f.size(); i++) {
    merge(dist, g[f[i]]);
  }
  int n = g.size();
  vector<int> max; //if new position is at i, then max[i] is the max nearest distance
  vector<int>::iterator it;
  for (i = 0; i < n; i++) {
    if (dist[i]) {  // if there's no fire station at i
      vector<int> d = dist;
      merge(d, g[i]);
      it = max_element(d.begin(), d.end());
      max.push_back(*it);
    }
    else {
      max.push_back(INT_MAX);
    }
  }
  it = min_element(max.begin(), max.end());
  return it - max.begin();
}

int main() {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int nf, nv;
    cin >> nf >> nv;
    vector<int> s;
    for (int j = 0; j < nf; j++) {
      int f;
      cin >> f;
      s.push_back(f - 1);  //we start from 0
    }
    vector<int>::iterator it = unique(s.begin(), s.end()); //it says fire stations may overlap
    s.erase(it, s.end());
    string line;
    getline(cin, line); //skip trailing '\n'
    Graph g(nv, vector<int>(nv));
    init(g);
    while (getline(cin, line) && !line.empty()) {
      istringstream is(line);
      int u, v;
      int w;
      is >> u >> v >> w;
      u--, v--; //we start from 0
      g[u][v] = w;
      g[v][u] = w;
    }
    if (i)
      cout << endl;
    cout << station(g, s) + 1 << endl;
  }
  return 0;
}
