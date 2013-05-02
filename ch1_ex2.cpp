#include <iostream>
#include <vector>

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Map;

bool load_map(Map & map) {
  map.clear();
  int n_row, n_col;
  cin >> n_row >> n_col;
  Map map;
  for (int i = 0; i < n_col; i++) {
    Row row(n_row);
    string line;
    getline(cin, line);
    for (int j = 0; j < n_row; j++) {
      row[j] =
    }
    map.push_back(row);
  }
  cin
}

void put_map(Map & map) {
}

void mark(Map & map) {

}

int main() {
  Map map;
  while (load_map(map)) {
    mark(map);
    put_map(map);
  }
}
