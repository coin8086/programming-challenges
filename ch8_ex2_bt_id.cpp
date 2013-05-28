#include <iostream>
#include <vector>
#include <set>
#include <cassert>

#define MAX_DEPTH 50

using namespace std;

typedef unsigned long long ull_t;
typedef vector<char> Board;

#ifdef DEBUG
#include <string>

void output_board(const Board & b, int depth = 0) {
  string sp(depth * 2, ' ');
  for (int i = 0; i < 4; i++) {
    cerr << sp;
    for (int j = 0; j < 4; j++) {
      if (j)
        cerr << ' ';
      cerr << (int)b[i * 4 + j];
    }
    cerr << endl;
  }
}

#else
#define output_board(...) ((void)(0))
#endif

ull_t value(const Board & b) {
  ull_t v = 0;
  for (int i = 0; i < 16; i++) {
    v *= 16;
    v += b[i];
  }
  return v;
}

//rotate 90 degree clockwise
Board rotate(const Board & b) {
  static int map[16] = {12, 8, 4, 0, 13, 9, 5, 1, 14, 10, 6, 2, 15, 11, 7, 3};
  Board r(16);
  for (int i = 0; i < 16; i++)
    r[i] = b[map[i]];
  return r;
}

static ull_t targets[4] = {0};

void init() {
  Board b(16, 0);
  for (int i = 0; i < 15; i++) {
    b[i] = i + 1;
  }
  targets[0] = value(b);
  for (int i = 1; i < 4; i++) {
    b = rotate(b);
    targets[i] = value(b);
  }
}

inline bool is_target(const Board & board) {
  ull_t v = value(board);
  for (int i = 0; i < 4; i++) {
    if (targets[i] == v)
      return true;
  }
  return false;
}

inline int space_index(const Board & board) {
  int i;
  for (i = 0; i < board.size(); i++) {
    if (!board[i])
      break;
  }
  assert(i != board.size());
  return i;
}

Board move(const Board & board, char step, int tip = 0) {
  int i = !board[tip] ? tip : space_index(board);
  int row = i / 4;
  int col = i % 4;
  switch (step) {
    case 'U':
      row--;
      assert(row >= 0);
      break;
    case 'D':
      row++;
      assert(row < 4);
      break;
    case 'L':
      col--;
      assert(col >= 0);
      break;
    case 'R':
      col++;
      assert(col < 4);
      break;
    default:
      assert("Invalid move!");
  }
  int newpos = row * 4 + col;
  Board new_board = board;
  new_board[i] = new_board[newpos];
  new_board[newpos] = 0;
  return new_board;
}

//This function has side effect: it add the board and its rotated symmetries
//into the searched set if they are not in the set yet.
inline bool to_do(const Board & board, set<ull_t> & searched) {
  ull_t v = value(board);
  bool r = searched.insert(v).second;
  if (r) {
    Board b = board;
    for (int i = 1; i < 4; i++) {
      b = rotate(b);
      searched.insert(value(b));
    }
  }
  return r;
}

vector<char> candidates(const Board & board, set<ull_t> & searched) {
  int i = space_index(board);
  int row = i / 4;
  int col = i % 4;
  vector<char> cand;
  if (row != 0 && to_do(move(board, 'U', i), searched))
    cand.push_back('U');
  if (row != 3 && to_do(move(board, 'D', i), searched))
    cand.push_back('D');
  if (col != 0 && to_do(move(board, 'L', i), searched))
    cand.push_back('L');
  if (col != 3 && to_do(move(board, 'R', i), searched))
    cand.push_back('R');
  return cand;
}

bool backtrack(const Board & board, vector<char> & steps, set<ull_t> & searched, int max_dep) {
  output_board(board, steps.size());
  if (is_target(board))
    return true;
  if (steps.size() >= max_dep)
    return false;
  vector<char> cand = candidates(board, searched);
  for (int i = 0; i < cand.size(); i++) {
    steps.push_back(cand[i]);
    Board next = move(board, cand[i]);
    if (backtrack(next, steps, searched, max_dep))
      return true;
    steps.pop_back();
  }
  return false;
}

inline bool run(const Board & board, vector<char> & steps, int max_dep) {
  set<ull_t> searched;
  to_do(board, searched);
  steps.clear();
  return backtrack(board, steps, searched, max_dep);
}

bool solve(Board & board, vector<char> & steps) {
  for (int i = 1; i <= MAX_DEPTH; i++) {
    if (run(board, steps, i))
      return true;
  }
  return false;
}

int main() {
  init();
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    Board board(16);
    for (int j = 0; j < 16; j++) {
      int ch;
      cin >> ch;
      board[j] = ch;
    }
    vector<char> steps;
    if (solve(board, steps)) {
      for (int k = 0; k < steps.size(); k++) {
        cout << steps[k];
      }
    }
    else {
      cout << "This puzzle is not solvable.";
    }
    cout << endl;
  }
}
