/***********************************************************
 * Servicing Stations
 * PC/UVa IDs: 110804/10160
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <climits>

#define MAX_TOWNS 35

using namespace std;

typedef map<int, vector<int> > Graph;
typedef long long llt;

//bfs g from vertex v and record visited vertexes in visited
void visit(const Graph & g, int v, set<int> & visited) {
  queue<int> q;
  visited.insert(v);
  q.push(v);
  while (!q.empty()) {
    int u = q.front();
    const vector<int> & vec = g.at(u);
    for (int i = 0; i < vec.size(); i++) {
      if (!visited.count(vec[i])) {
        visited.insert(vec[i]);
        q.push(vec[i]);
      }
    }
    q.pop();
  }
}

//get a subgraph from g, with only vertexes in s
Graph subgraph(const Graph & g, const set<int> & s) {
  Graph ng;
  if (g.size() == s.size()) {
    ng = g;
  }
  else {
    set<int>::const_iterator it = s.begin();
    for (; it != s.end(); it++) {
      int v = *it;
      ng[v] = g.at(v);
      vector<int> & vec = ng[v];
      int i, j;
      for (i = vec.size() - 1, j = i; i >= 0; i--) {
        if (!s.count(vec[i])) {
          if (i != j)
            swap(vec[i], vec[j]);
          j--;
        }
      }
      vec.resize(j + 1);
    }
  }
  return ng;
}

//get max connected subgraphs from g
vector<Graph> conn_graphs(const Graph & g) {
  vector<Graph> gs;
  set<int> visited;
  Graph::const_iterator it = g.begin();
  while (visited.size() != g.size()) {
    int v;
    for (; it != g.end(); it++) {
      if (!visited.count(it->first)) {
        v = it->first;
        break;
      }
    }
    set<int> accessed;
    visit(g, v, accessed);
    gs.push_back(subgraph(g, accessed));
    visited.insert(accessed.begin(), accessed.end());
  }
  return gs;
}

inline vector<int> vertexes(const Graph & g) {
  vector<int> r;
  r.reserve(g.size());
  Graph::const_iterator it = g.begin();
  for (; it != g.end(); it++) {
    r.push_back(it->first);
  }
  return r;
}

inline llt vec_to_llt(const vector<bool> & vec) {
  llt r = 0;
  for (int i = vec.size() - 1; i >= 0; i--) {
    r = r << 1;
    if (vec[i])
      r |= 1;
  }
  return r;
}

inline llt to_llt(int n, const vector<int> & vec) {
  vector<bool> v(n);
  for (int i = 0; i < n; i++) {
    if (find(vec.begin(), vec.end(), i) != vec.end()) {
      v[i] = true;
    }
  }
  return vec_to_llt(v);
}

template<typename Success>
bool combine(int total, int wanted, vector<int> & selected, Success & success)
{
  if (selected.size() == wanted) {
    return success(selected);
  }
  else {
    int idx = selected.size() ? selected.back() + 1 : 0;
    for (int i = idx; i < total; i++) {
      selected.push_back(i);
      if (combine(total, wanted, selected, success))
        return true;
      selected.pop_back();
    }
  }
  return false;
}

class Checker {
public:
  Checker(const vector<llt> & towns, llt target) : _towns(towns), _target(target) {}

  bool operator ()(const vector<int> & selected) {
    llt t = 0;
    for (int i = 0; i < selected.size(); i++) {
      t |= _towns[selected[i]];
    }
    return t == _target;
  }

private:
  const vector<llt> & _towns;
  llt _target;
};

int serv_station(const Graph & g) {
  int r = 0;
  //Split a graph into several connected subgraphs. This is A KEY OPTIMIZATION in speed.
  vector<Graph> gs = conn_graphs(g);
  for (int j = 0; j < gs.size(); j++) {
    //Build towns vector, each dimension representing a town and its neighbours.
    vector<llt> towns;
    Graph::iterator it = gs[j].begin();
    for (; it != gs[j].end(); it++) {
      //In a connected graph with more than 2 vertexes, we select a vertex only
      //when it has a degree bigger than 1. This is A KEY OPTIMIZATION in speed.
      if (gs[j].size() < 3 || it->second.size() > 1) {
        it->second.push_back(it->first);
        towns.push_back(to_llt(g.size(), it->second));
      }
    }
    //The target represents all the towns in a max connected subgraph.
    llt target = to_llt(g.size(), vertexes(gs[j]));
    Checker checker(towns, target);
    //Select i towns from all to check if we make it. It's like an Iterative Deepening.
    int i;
    for (i = 1; i <= gs[j].size(); i++) {
      vector<int> sel;
      if (combine(towns.size(), i, sel, checker))
        break;
    }
    r += i;
  }
  return r;
}

int main() {
  int n, m;
  while ((cin >> n >> m) && n && m) {
    Graph g;
    int i;
    for (i = 0; i < n; i++) {
      g[i] = vector<int>();
    }
    for (i = 0; i < m; i++) {
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
