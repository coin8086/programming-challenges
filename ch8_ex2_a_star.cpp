/***********************************************************
 * 15-Puzzle Problem
 * PC/UVa IDs: 110802/10181
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>
#ifdef DEBUG
#include <string>
#endif

#define MAX_DEPTH 50

using namespace std;

typedef unsigned long long ull_t;
typedef unsigned int uint;
typedef vector<char> Moves;

class Board {
public:
  Board() {}

  Board(vector<char> & vec) {
    _vec.swap(vec);
  }

  Board(const Board & b) {
    _vec = b._vec;
  }

  Board & operator =(const Board & b) {
    _vec = b._vec;
  }

  //used as hash key
  ull_t value() const {
    ull_t v = 0;
    for (int i = 0; i < 16; i++) {
      v *= 16;
      v += _vec[i];
    }
    return v;
  }

  //h*(), the less the better
  int score() const {
    int s = 0;
    for (int i = 0; i < _vec.size() - 1; i++) {
      if (_vec[i] != i + 1)
        s++;
    }
    return s;
  }

  //for priority queue
  bool operator <(const Board & b) const {
    return score() > b.score();
  }

  Moves valid_moves() const {
    int i = space_index();
    int row = i / 4;
    int col = i % 4;
    Moves cand;
    if (row != 0)
      cand.push_back('U');
    if (row != 3)
      cand.push_back('D');
    if (col != 0)
      cand.push_back('L');
    if (col != 3)
      cand.push_back('R');
    return cand;
  }

  Board move(char step, int tip = 0) const {
    int i = !_vec[tip] ? tip : space_index();
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
    Board new_board = *this;
    new_board._vec[i] = new_board._vec[newpos];
    new_board._vec[newpos] = 0;
    return new_board;
  }

  static Board target() {
    Board b;
    b._vec.resize(16);
    for (int i = 0; i < 15; i++) {
      b._vec[i] = i + 1;
    }
    return b;
  }

  void debug(int depth = 0) const {
#ifdef DEBUG
    string sp(depth * 2, ' ');
    for (int i = 0; i < 4; i++) {
      cerr << sp;
      for (int j = 0; j < 4; j++) {
        if (j)
          cerr << ' ';
        cerr << (int)_vec[i * 4 + j];
      }
      cerr << endl;
    }
#endif
  }

private:
  int space_index() const {
    int i;
    for (i = 0; i < _vec.size(); i++) {
      if (!_vec[i])
        break;
    }
    assert(i != _vec.size());
    return i;
  }

  vector<char> _vec;
};

class State {
public:
  State() : parent(0), depth(0), step(0) {}
  State(ull_t p, uint d, char s) : parent(p), depth(d), step(s) {}

  ull_t parent;
  uint depth;
  char step;
};

typedef map<ull_t, State> Searched;

static ull_t target_value;

inline void init() {
  Board b = Board::target();
  target_value = b.value();
}

void build_path(ull_t v, const Searched & searched, Moves & steps) {
  Searched::const_iterator it = searched.find(v);
  while (it != searched.end()) {
    const State & s = it->second;
    steps.push_back(s.step);
    it = searched.find(s.parent);
  }
  //pop up the first step, which must be 0, rather than one of U,D,L,R
  steps.pop_back();
  reverse(steps.begin(), steps.end());
}

bool solve(Board & board, Moves & steps) {
  bool r = false;
  priority_queue<Board> q;
  Searched searched;
  searched[board.value()] = State();
  q.push(board);
  while (!q.empty()) {
    Board b = q.top();
    q.pop();
    ull_t v = b.value();
    if (v == target_value) {
      build_path(v, searched, steps);
      r = true;
      break;
    }
    uint depth = searched[v].depth;
    b.debug(depth);
    if (depth <= MAX_DEPTH) {
      Moves cand = b.valid_moves();
      for (int i = 0; i< cand.size(); i++) {
        Board n = b.move(cand[i]);
        ull_t nv = n.value();
        Searched::iterator it = searched.find(nv);
        if (it == searched.end()) {
          searched[nv] = State(v, depth + 1, cand[i]);
          q.push(n);
        }
        else if (depth + 1 < it->second.depth) {
          State & s = it->second;
          s.parent = v;
          s.depth = depth + 1;
          s.step = cand[i];
          q.push(n);
        }
      }
    }
  }
  return r;
}

int main() {
  init();
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    vector<char> vec(16);
    for (int j = 0; j < 16; j++) {
      int ch;
      cin >> ch;
      vec[j] = ch;
    }
    Board board(vec);
    Moves steps;
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
