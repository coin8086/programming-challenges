#if !defined(NDEBUG) && !defined(DEBUG)
#define NDEBUG
#endif

#include <cassert>

#ifdef DEBUG
#include "../comm_headers/debug_helper.h"
#else
#define DEBUG_OUT(...)
#endif

#include <iostream>
#include <sstream>
#include <deque>


using namespace std;

#define MAX_STEPS 10000

#define VALUES "23456789TJQKA"

#define SUITS "cdhs"

int card(char n, char s) {
  for (int i = 0; i < 13; i++) {
    if (VALUES[i] == n) {
      for (int j = 0; j < 4; j++)
        if (SUITS[j] == s)
          return i * 4 + j;
    }
  }
  assert(0 && "Something wrong!");
  return -1;
}

inline char value(int card) {
  assert(card >= 0 && card < 52);
  return VALUES[card / 4];
}

inline int nvalue(int card) {
  assert(card >= 0 && card < 52);
  return card / 4;
}

inline char suit(int card) {
  assert(card >= 0 && card < 52);
  return SUITS[card % 4];
}

bool load_line(deque<int> & q) {
  string line;
  if (!getline(cin, line))
    return false;
  istringstream is(line);
  char n, s;
  while(is >> n >> s)
    q.push_back(card(n, s));
  return true;
}

bool load_input(deque<int> & a, deque<int> & b) {
  a.clear();
  b.clear();
  return load_line(a) && load_line(b);
}

inline void clear(deque<int> & c, deque<int> & player) {
  //TODO: use alg copy?
  while(!c.empty()) {
    player.push_back(c.front());
    c.pop_front();
  }
}

int war(deque<int> & a, deque<int> & b) {
  assert(a.size() == b.size());
  deque<int> c;
  bool in_war = false;
  int steps = 0;
  while(!a.empty() && !b.empty() && steps < MAX_STEPS) {
    steps++;
    int x = a.front();
    int y = b.front();
    a.pop_front();
    b.pop_front();
    c.push_back(x);
    c.push_back(y);
    DEBUG_OUT("[step %d]\ta: %c%c b: %c%c", steps, value(x), suit(x), value(y), suit(y));
    if (in_war) {
      in_war = false;
      DEBUG_OUT("\n");
    }
    else {
      int vx = nvalue(x);
      int vy = nvalue(y);
      if (vx > vy) {
        clear(c, a);
        DEBUG_OUT(" \ta win\n");
      }
      else if (vx < vy) {
        clear(c, b);
        DEBUG_OUT(" \tb win\n");
      }
      else {
        in_war = true;
        DEBUG_OUT(" \tdraw\n");
      }
    }
  }
  return steps;
}

int main() {
  deque<int> a;
  deque<int> b;

  while (load_input(a, b)) {
    int steps = war(a, b);
    cout << steps << " steps";
    if (!a.empty() && b.empty()) {
      cout << " a win" << endl;
    }
    else if (a.empty() && !b.empty()) {
      cout << " b win" << endl;
    }
    else if (a.empty() && b.empty()) {
      cout << " draw" << endl;
    }
    else {
      cout << " max steps limit" << endl;
    }
  }
  return 0;
}
