#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cstdio>
//#include <csignal>
#include <cstdlib>
#include <cassert>

#define MAX_DEPTH 50

using namespace std;

typedef unsigned char byte;

typedef unsigned long long ull;

ull g_counter = 0;

class State {
private:
  byte _value[16];
  int _score; //result of h*(n) of A*, the less the better

  State() : _depth(0), _move(0) {}

  void computeScore() { //h*(n) of A*
    int s = 0;
    for (int i = 0; i < 15; i++) {
      if (_value[i] != i + 1)
        s++;
    }
    _score = s;
  }

public:
  mutable int _depth; //also serves as g(n) of A*
  mutable char _move;

  bool operator ==(const State & rhs) const {
    return memcmp(_value, rhs._value, 16) == 0;
  }

  bool operator <(const State & rhs) const {
    return memcmp(_value, rhs._value, 16) < 0;
  }

  int score() const { return _score; }

  void zeroIndex(int & i, int & j) const {
    int k = 0;
    for (; k < 16; k++)
      if (!_value[k])
        break;

    i = k / 4;
    j = k % 4;
  }

  State next(char move, int i = -1, int j = -1) const {
    if (i == -1)
      zeroIndex(i, j);

    State n = *this;
    switch (move) {
      case 'U':
        n._value[4 * (i - 1) + j] = 0;
        n._value[4 * i + j] = _value[4 * (i - 1) + j];
        n._move = 'U';
        break;
      case 'D':
        n._value[4 * (i + 1) + j] = 0;
        n._value[4 * i + j] = _value[4 * (i + 1) + j];
        n._move = 'D';
        break;
      case 'L':
        n._value[4 * i + j - 1] = 0;
        n._value[4 * i + j] = _value[4 * i + j - 1];
        n._move = 'L';
        break;
      case 'R':
        n._value[4 * i + j + 1] = 0;
        n._value[4 * i + j] = _value[4 * i + j + 1];
        n._move = 'R';
        break;
      default:
        assert(0);
    }
    return n;
  }

  vector<State> nextMoves() const {
    int i, j;
    zeroIndex(i, j);
    vector<State> ret;
    if (i > 0) { //move up
      State n = next('U', i, j);
      n.computeScore();
      ret.push_back(n);
    }
    if (i < 3) { //move down
      State n = next('D', i, j);
      n.computeScore();
      ret.push_back(n);
    }
    if (j > 0) { //move left
      State n = next('L', i, j);
      n.computeScore();
      ret.push_back(n);
    }
    if (j < 3) { //move right
      State n = next('R', i, j);
      n.computeScore();
      ret.push_back(n);
    }
    return ret;
  }

  //See
  //https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
  //for the formula and why.
  bool solvable() const {
    int inverse = 0;
    for (int k = 0; k < 16; k++) {
      int n = _value[k];
      for (int l = k + 1; l < 16; l++) {
        if (_value[l] < n && _value[l])
          inverse++;
      }
    }

    int i, j;
    zeroIndex(i, j);

    return (i % 2 == 0) ? (inverse % 2 == 1) : (inverse % 2 == 0);
  }

  void print() const {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        printf("%2d ", _value[4 * i + j]);
      }
      printf("\n");
    }
    printf("score: %2d, _depth: %2d\n", _score, _depth);
  }

  static State target;

  static void init() {
    for (int i = 0; i < 15; i++) {
      target._value[i] = i + 1;
    }
    target._value[15] = 0;
    target._score = 0;
  }

  static State create(char array[4][4]) {
    State inst;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        inst._value[4 * i + j] = array[i][j];
      }
    }
    inst.computeScore();
    return inst;
  }

  //For "<" operator between two State objects
  class PriorityComparer : less<State> {
  public:
    bool operator() (const State & a, const State & b) {
      return a.score() > b.score();
    }
  };
};

State State::target;

vector<char> rebuild_path(const set<State> & closed, set<State>::const_iterator it) {
  vector<char> ret;
  while (it->_move) {
    ret.push_back(it->_move);
    char move; //move back to previous state
    switch(it->_move) {
      case 'U':
        move = 'D';
        break;
      case 'D':
        move = 'U';
        break;
      case 'L':
        move = 'R';
        break;
      case 'R':
        move = 'L';
        break;
      default:
        assert(0);
    }
    State s = it->next(move);
    it = closed.find(s);
    assert(it != closed.end());
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

void solve(char array[4][4]) {
  State s = State::create(array);
  if (!s.solvable()) {
    cout << "This puzzle is not solvable." << endl;
    return;
  }

  //See 《算法技术手册》(O'Reilly) page 198 for A* search
  set<State> closed;
  priority_queue<State, vector<State>, State::PriorityComparer> open;
  open.push(s);
  while (!open.empty()) {
    State e = open.top();
    open.pop();
    closed.insert(e);
    ++g_counter;

    if (e == State::target)
      break;

    if (e._depth > MAX_DEPTH)
      continue;

    vector<State> moves = e.nextMoves();
    for (int i = 0; i < moves.size(); i++) {
      State & n = moves[i];
      n._depth = e._depth + 1;
      set<State>::iterator it = closed.find(moves[i]);
      if (it != closed.end()) {
        if (it->_depth < n._depth)
          continue;
        else
          closed.erase(it);
      }
      open.push(n);
    }
  }

  set<State>::iterator it = closed.find(State::target);
  if (it != closed.end()) {
    vector<char> steps = rebuild_path(closed, it);
    for (int i = 0; i < steps.size(); i++) {
      cout << steps[i];
    }
  }
  else { // Not solvable within MAX_DEPTH
    cout << "This puzzle is not solvable.";
  }
  cout << endl;
}

//void signalHandler(int signum) {
//  cout << "Interrupt signal (" << signum << ") received.\n";
//  cout << "Searched: " << g_counter << endl;
//  exit(signum);
//}

int main() {
  //signal(SIGINT, signalHandler);
  State::init();
  int n;
  cin >> n;
  for (int t = 0; t < n; t++) {
    char a[4][4];
    int ch;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        cin >> ch;
        a[i][j] = ch;
      }
    }
    solve(a);
  }
  return 0;
}
