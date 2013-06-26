/***********************************************************
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Method {
  NOOP = -1,
  MATCH = 0,
  INSERT,
  DELETE
};

class Cell {
public:
  int cost;
  Method method;
};

typedef vector<vector<Cell> > Grid;

void init(Grid & grid) {
  int i, j;
  int row = grid.size();
  int col = grid[0].size();
  for (i = 0; i < row; i++) {
    Cell & c = grid[i][0];
    c.cost = i;
    c.method = DELETE;
  }
  for (j = 0; j < col; j++) {
    Cell & c = grid[0][j];
    c.cost = j;
    c.method = INSERT;
  }
  grid[0][0].method = NOOP;
}

inline void match_out(const string & s, const string & t, int i, int j) {
  cout << "[M] '" << s[i - 1] << "' <-> '" << t[j - 1] << "'" << endl;
}

inline void insert_out(const string & t, int j) {
  cout << "[I] '" << t[j - 1] << "'" << endl;
}

inline void delete_out(const string & s, int i) {
  cout << "[D] '" << s[i - 1] << "'" << endl;
}

void build_path(const Grid & grid, const string & s, const string & t, int i, int j) {
  switch (grid[i][j].method) {
    case MATCH:
      build_path(grid, s, t, i - 1, j - 1);
      match_out(s, t, i, j);
      break;

    case INSERT:
      build_path(grid, s, t, i, j - 1);
      insert_out(t, j);
      break;

    case DELETE:
      build_path(grid, s, t, i - 1, j);
      delete_out(s, i);
      break;
  }
}

inline int match(char s, char t) {
  return s == t ? 0 : 1;
}

inline int indel(char c) {
  return 1;
}

inline void goal_cell(const string & s, const string & t, int & i, int & j) {
  i = s.size();
  j = t.size();
}

int edit_distance(const string & s, const string & t) {
  int row = s.size() + 1;
  int col = t.size() + 1;
  Grid grid(row, vector<Cell>(col));
  init(grid);
  int i, j;
  for (i = 1; i < row; i++) {
    for (j = 1; j < col; j++) {
      int opt[3];
      opt[0] = grid[i - 1][j - 1].cost + match(s[i - 1], t[j - 1]);
      opt[1] = grid[i][j - 1].cost + indel(t[j - 1]);
      opt[2] = grid[i - 1][j].cost + indel(s[i - 1]);
      int m = opt[0];
      int mi = 0;
      for (int k = 1; k < 3; k++) {
        if (opt[k] < m) {
          m = opt[k];
          mi = k;
        }
      }
      grid[i][j].cost = m;
      grid[i][j].method = (Method)mi;
    }
  }
  goal_cell(s, t, i, j);
  build_path(grid, s, t, i, j);
  return grid[i][j].cost;
}

int main() {
  int n = 0;
  cin >> n;
  string emptyline;
  getline(cin, emptyline);
  for (int i = 0; i < n; i++) {
    string s, t;
    getline(cin, s);
    getline(cin, t);
    cout << edit_distance(s, t) << endl;
  }
  return 0;
}
