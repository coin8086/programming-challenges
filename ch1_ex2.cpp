#include <iostream>
#include <vector>

#ifdef DEBUG
#include "../comm_headers/debug_helper.h"
#else
#define DEBUG_OUT(...)
#endif

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Map;

bool load_map(Map & map) {
  map.clear();
  int n_row, n_col;
  cin >> n_row >> n_col;
  if (!(n_row && n_col && cin))
    return false;

  DEBUG_OUT("row: %d col: %d\n", n_row, n_col);
  for (int i = 0; i < n_row; i++) {
    Row row(n_col);
    for (int j = 0; j < n_col; j++) {
      cin >> row[j];
    }
    map.push_back(row);
  }
  return true;
}

void put_map(Map & map, int n) {
  cout << "Field #" << n << ":" << endl;
  for (int i = 0; i < map.size(); i++) {
    Row & r = map[i];
    for (int j = 0; j < r.size(); j++) {
      cout << r[j];
    }
    cout << endl;
  }
}

inline void increase(Map & map, int row, int col, int max_row, int max_col) {
  if (row < 0 || row >= max_row || col < 0 || col >= max_col)
    return;

  char ch = map[row][col];
  if (ch != '*') {
    if (ch == '.') {
      map[row][col] = '1';
    }
    else {
      map[row][col]++;
    }
  }
}

void update_neighbors(Map & map, int row, int col) {
  int up = row - 1;
  int down = row + 1;
  int left = col - 1;
  int right = col + 1;
  int max_row = map.size();
  int max_col = map[0].size();
  increase(map, up, left, max_row, max_col);
  increase(map, up, col, max_row, max_col);
  increase(map, up, right, max_row, max_col);
  increase(map, row, left, max_row, max_col);
  increase(map, row, right, max_row, max_col);
  increase(map, down, left, max_row, max_col);
  increase(map, down, col, max_row, max_col);
  increase(map, down, right, max_row, max_col);
}

void mark(Map & map) {
  for (int i = 0; i < map.size(); i++) {
    Row & r = map[i];
    for (int j = 0; j < r.size(); j++) {
      if (r[j] == '*') {
        update_neighbors(map, i, j);
      }
      else if (r[j] == '.') {
        r[j] = '0';
      }
    }
  }
}

int main() {
  Map map;
  int n = 0;
  while (load_map(map)) {
    ++n;
    mark(map);
    if (n != 1)
      cout << endl;
    put_map(map, n);
  }
}
