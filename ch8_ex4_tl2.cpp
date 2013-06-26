/***********************************************************
 * Servicing Stations
 * PC/UVa IDs: 110804/10160
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef vector<vector<bool> > Graph;
typedef long long llt;

inline llt vec_to_llt(const vector<bool> & vec) {
  llt r = 0;
  for (int i = vec.size() - 1; i >= 0; i--) {
    r = r << 1;
    if (vec[i])
      r |= 1;
  }
  return r;
}

int bt(const vector<llt> & towns, llt t, int i = -1, llt a = 0) {
  if (t == a)
    return 0;
  int min = INT_MAX;
  for (int j = i + 1; j < towns.size(); j++) {
    int m = bt(towns, t, j, a | towns[j]);
    if (m < min)
      min = m;
    if (!min)
      break;
  }
  return min == INT_MAX ? INT_MAX : min + 1;
}

int serv_station(Graph & g) {
  vector<llt> towns;
  int i;
  for (i = 0; i < g.size(); i++) {
    g[i][i] = true;
    towns.push_back(vec_to_llt(g[i]));
  }
  return bt(towns, vec_to_llt(vector<bool>(g.size(), true)));
}

int main() {
  int n, m;
  while ((cin >> n >> m) && n && m) {
    Graph g(n, vector<bool>(n));
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--; //we start from 0
      g[u][v] = true;
      g[v][u] = true;
    }
    cout << serv_station(g) << endl;
  }
  return 0;
}
