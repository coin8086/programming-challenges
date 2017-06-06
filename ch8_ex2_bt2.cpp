#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cstring>
#include <cstdio>
#include <csignal>
#include <cstdlib>

using namespace std;

typedef unsigned char byte;

typedef unsigned long long ull;

ull g_counter = 0;

class State {
private:
  byte s[16];

public:
  State() { memset(s, 0, 16); }

  bool operator ==(const State & rhs) const {
    return memcmp(s, rhs.s, 16) == 0;
  }

  ull hashCode() const {
    ull code = 0;
    int m = 0;
    for (int i = 0; i < 16; i++) {
      ull t = s[i];
      code |= t << m;
      m += 4;
    }
    return code;
  }

  typedef pair<State, char> Move;

  vector<Move> nextMoves() const {
    vector<Move> ret;
    int k = 0;
    for (; k < 16; k++)
      if (!s[k])
        break;

    int i = k / 4;
    int j = k % 4;

    if (i > 0) { //move up
      State n = *this;
      n.s[4 * (i - 1) + j] = 0;
      n.s[4 * i + j] = s[4 * (i - 1) + j];
      ret.push_back(Move(n, 'U'));
    }
    if (i < 3) { //move down
      State n = *this;
      n.s[4 * (i + 1) + j] = 0;
      n.s[4 * i + j] = s[4 * (i + 1) + j];
      ret.push_back(Move(n, 'D'));
    }
    if (j > 0) { //move left
      State n = *this;
      n.s[4 * i + j - 1] = 0;
      n.s[4 * i + j] = s[4 * i + j - 1];
      ret.push_back(Move(n, 'L'));
    }
    if (j < 3) { //move right
      State n = *this;
      n.s[4 * i + j + 1] = 0;
      n.s[4 * i + j] = s[4 * i + j + 1];
      ret.push_back(Move(n, 'R'));
    }
    return ret;
  }

  static State target;

  static void init() {
    for (int i = 0; i < 15; i++) {
      target.s[i] = i + 1;
    }
  }

  static State create(char array[4][4]) {
    State inst;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        inst.s[4 * i + j] = array[i][j];
      }
    }
    return inst;
  }

  void print() const {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        printf("%2d ", s[4 * i + j]);
      }
      printf("\n");
    }
    printf("hash: %016llX\n", hashCode());
  }
};

State State::target; //damn the C++!

bool search(const State & s, vector<char> & steps, set<ull> visited) {
  if (s == State::target)
    return true;

  if (steps.size() > 50)
    return false;

  //s.print();
  g_counter++;
  visited.insert(s.hashCode());

  vector<State::Move> moves = s.nextMoves();
  for (int i = 0; i < moves.size(); i++) {
    State::Move m = moves[i];
    if (!visited.count(m.first.hashCode())) {
      steps.push_back(m.second);
      if (search(m.first, steps, visited))
        return true;
      steps.pop_back();
    }
  }
  return false;
}

void solve(char array[4][4]) {
  State s = State::create(array);
  vector<char> steps;
  set<ull> visited;
  if (search(s, steps, visited)) {
    for (int i = 0; i < steps.size(); i++) {
      cout << steps[i];
    }
  }
  else {
    cout << "This puzzle is not solvable.";
  }
  cout << endl;
}

void signalHandler(int signum) {
  cout << "Interrupt signal (" << signum << ") received.\n";
  cout << "Searched: " << g_counter << endl;
  exit(signum);
}

int main() {
  signal(SIGINT, signalHandler);

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
