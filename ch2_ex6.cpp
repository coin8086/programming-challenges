/***********************************************************
 * Erdos Numbers
 * PC/UVa IDs: 110206/10044
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cctype>
#include <climits>

#define ERDOS "Erdos, P."

using namespace std;

typedef map<string, set<string> > Relation;

inline void skip_space(const string & str, int & i) {
  while (isspace(str[i]))
    i++;
}

inline bool is_valid(char ch) {
  return ch && !isspace(ch) && ch != ',';
}

inline string parse_author(const string & line, int start = 0, int * end = 0) {
  string a;
  int i = start;
  skip_space(line, i);
  while (is_valid(line[i]))
    a.push_back(line[i++]);
  skip_space(line, i);
  if (line[i] == ',') {
    a.push_back(',');
    a.push_back(' ');
    i++;
  }
  skip_space(line, i);
  while (is_valid(line[i]))
    a.push_back(line[i++]);
  if (end)
    *end = i;
  return a;
}

inline vector<string> parse_authors(const string & line) {
  vector<string> a;
  string names = line.substr(0, line.find(':'));
  int i = 0;
  int j;
  while (true) {
    string name = parse_author(names, i, &j);
    if (!name.empty())
      a.push_back(name);
    skip_space(names, j);
    if (names[j] == ',')
      j++;
    skip_space(names, j);
    if (!names[j])
      break;
    i = j;
  }
  return a;
}

inline void relate(Relation & r, const vector<string> & authors) {
  int n = authors.size();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      r[authors[i]].insert(authors[j]);
      r[authors[j]].insert(authors[i]);
    }
  }
}

vector<int> erdos_numbers(const Relation & r, const vector<string> & authors) {
  vector<int> en(authors.size(), INT_MAX);
  if (r.count(ERDOS)) { //Erdos himself may not in r at all!
    map<string, int> stat;
    queue<string> q;
    stat[ERDOS] = 0;
    q.push(ERDOS);
    while (!q.empty()) {
      string author = q.front();
      q.pop();
      int n = stat[author];
      const set<string> & coauthors = r.at(author);
      set<string>::const_iterator it = coauthors.begin();
      for (; it != coauthors.end(); it++) {
        if (!stat.count(*it)) {
          stat[*it] = n + 1;
          q.push(*it);
        }
      }
    }
    for (int i = 0; i < authors.size(); i++) {
      map<string, int>::iterator it = stat.find(authors[i]);
      if (it != stat.end())
        en[i] = it->second;
    }
  }
  return en;
}

int main() {
  int N = 0;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    int p, n;
    cin >> p >> n;
    Relation r;
    string line;
    getline(cin, line); //Skip empty line
    int j;
    for (j = 0; j < p; j++) {
      getline(cin, line);
      relate(r, parse_authors(line));
    }
    vector<string> authors;
    authors.reserve(n);
    for (j = 0; j < n; j++) {
      getline(cin, line);
      authors.push_back(parse_author(line));
    }
    vector<int> en = erdos_numbers(r, authors);
    cout << "Scenario " << i << endl;
    for (j = 0; j < n; j++) {
      cout << authors[j] << ' ';
      if (en[j] == INT_MAX)
        cout << "infinity";
      else
        cout << en[j];
      cout << endl;
    }
  }
  return 0;
}
