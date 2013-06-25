#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void track_paths(const vector<vector<int> > & g, int i, int j,
  const string & s1, const string & s2, string & path, vector<string> & paths)
{
  if (!i || !j) {
    paths.push_back(path);
  }
  else {
    vector<pair<int, int> > next;
    bool changed = false;
    if (s1[i - 1] == s2[j - 1]) {
      path.push_back(s1[i - 1]);
      changed = true;
      next.push_back(make_pair(i - 1, j - 1));
    }
    else {
      int l1 = g[i - 1][j];
      int l2 = g[i][j - 1];
      if (l1 > l2)
        next.push_back(make_pair(i - 1, j));
      else if (l1 < l2)
        next.push_back(make_pair(i, j - 1));
      else {
        next.push_back(make_pair(i - 1, j));
        next.push_back(make_pair(i, j - 1));
      }
    }
    for (int k = 0; k < next.size(); k++) {
      track_paths(g, next[k].first, next[k].second, s1, s2, path, paths);
    }
    if (changed)
      path.erase(path.end() - 1);
  }
}

string lcs(const string & s1, const string & s2) {
  vector<vector<int> > l(s1.size() + 1, vector<int>(s2.size() + 1));
  for (int i = 1; i <= s1.size(); i++) {
    for (int j = 1; j <= s2.size(); j++) {
      if (s1[i - 1] == s2[j - 1]) {
        l[i][j] = l[i - 1][j - 1] + 1;
      }
      else {
        int l1 = l[i - 1][j];
        int l2 = l[i][j - 1];
        if (l1 >= l2)
          l[i][j] = l1;
        else
          l[i][j] = l2;
      }
    }
  }
  vector<string> paths;
  string path;
  track_paths(l, s1.size(), s2.size(), s1, s2, path, paths);
  for (int i = 0; i < paths.size(); i++)
    sort(paths[i].begin(), paths[i].end());
  sort(paths.begin(), paths.end());
  return string(paths[0]);
}

int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    cout << lcs(s1, s2) << endl;
  }
  return 0;
}
