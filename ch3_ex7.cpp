/***********************************************************
 * Doublets
 * PC/UVa IDs: 110307/10150
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <cassert>

using namespace std;

bool doublet(const string & a, const string & b) {
  bool diff = false;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      if (!diff)
        diff = true;
      else
        return false;
    }
  }
  assert(diff);
  return true;
}

typedef map<string, vector<string> > Graph;
typedef map<string, string> Pred;

vector<string> build_path(const Pred & pred, const string & t) {
  vector<string> path;
  path.push_back(t);
  Pred::const_iterator it;
  string d = t;
  while ((it = pred.find(d)) != pred.end()) {
    d = (*it).second;
    path.push_back(d);
  }
  reverse(path.begin(), path.end());
  return path;
}

bool search(const Graph & graph, const string & s, const string & t, vector<string> & path) {
  if (s.size() != t.size())
    return false;

  set<string> visited;
  Pred pred;
  deque<string> q;
  q.push_back(s);
  visited.insert(s);
  bool found = false;
  while (!q.empty() && !found) {
    string w = q.front();
    q.pop_front();
    const vector<string> & doublets = graph.at(w);
    for (int i = 0; i < doublets.size(); i++) {
      const string & d = doublets[i];
      if (d == t) {
        found = true;
        pred[t] = w;
        path = build_path(pred, t);
        break;
      }
      else if (!visited.count(d)) {
        visited.insert(d);
        q.push_back(d);
        pred[d] = w;
      }
    }
  }
  return found;
}

int main() {
  Graph graph;
  vector<vector<string> > dict(17);
  string line;
  while (getline(cin, line) && !line.empty()) {
    vector<string> & doublets = graph[line];
    vector<string> & words = dict[line.size()];
    for (int i = 0; i < words.size(); i++) {
      if (doublet(words[i], line)) {
        graph[words[i]].push_back(line);
        doublets.push_back(words[i]);
      }
    }
    words.push_back(line);
  }
  bool first = true;
  string s, t;
  while (cin >> s >> t) {
    if (first) {
      first = false;
    }
    else {
      cout << endl;
    }
    vector<string> path;
    if (search(graph, s, t, path)) {
      for (int i = 0; i < path.size(); i++) {
        cout << path[i] << endl;
      }
    }
    else {
      cout << "No solution." << endl;
    }
  }
  return 0;
}
