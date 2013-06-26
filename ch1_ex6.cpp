/***********************************************************
 * Interpreter
 * PC/UVa IDs: 110106/10033
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <string>

#ifdef DEBUG
#include "../comm_headers/debug_helper.h"
#else
#define DEBUG_OUT(...)
#endif

using namespace std;

class Instruction {
public:
  char first;
  char second;
  char third;
  Instruction() : first(0), second(0), third(0) {}
  Instruction(char ch1, char ch2, char ch3) : first(ch1 - '0'), second(ch2 - '0'), third(ch3 - '0') {}

  static int to_int(const Instruction & ins) {
    return ins.third + ins.second * 10 + ins.first * 100;
  }

  static Instruction from_int(int i) {
    Instruction ins;
    if (i) {
      if (i < 100) {
        ins.first = 0;
        ins.second = i / 10;
        ins.third = i % 10;
      }
      else {
        ins.first = i / 100;
        int r = i % 100;
        ins.second = r / 10;
        ins.third = r % 10;
      }
    }
    return ins;
  }
};

typedef vector<Instruction> Program;

void load_program(Program & p) {
  string line;
  p.clear();
  while (getline(cin, line)) {
    if (line.size() == 0)
      break;
    p.push_back(Instruction(line[0], line[1], line[2]));
  }
  p.resize(1000);
}

inline void overflow(int & n) {
  if (n >= 1000)
    n %= 1000;
}

int run_program(Program & p) {
  vector<int> r(10, 0);
  int i = 0;
  bool halt = false;
  int count = 0;

  while (!halt) {
    Instruction & ins = p[i++];
    count++;

    DEBUG_OUT("[%03d]%d%d%d: ", i - 1, ins.first, ins.second, ins.third);

    switch (ins.first) {
      case 0: //0ds
        DEBUG_OUT("r%d(%d)?\n", ins.third, r[ins.third]);
        if (r[ins.third]) {
          i = r[ins.second];
          DEBUG_OUT("... goto [%03d]\n", i);
        }
      break;

      case 1:
        halt = true;
        DEBUG_OUT("halt\n");
      break;

      case 2: //2dn
        r[ins.second] = ins.third;
        DEBUG_OUT("r%d=%d\n", ins.second, r[ins.second]);
      break;

      case 3: //3dn
        r[ins.second] += ins.third;
        overflow(r[ins.second]);
        DEBUG_OUT("r%d=%d\n", ins.second, r[ins.second]);
      break;

      case 4: //4dn
        r[ins.second] *= ins.third;
        overflow(r[ins.second]);
        DEBUG_OUT("r%d=%d\n", ins.second, r[ins.second]);
      break;

      case 5: //5ds
        r[ins.second] = r[ins.third];
        DEBUG_OUT("r%d=%d\n", ins.second, r[ins.second]);
      break;

      case 6: //6ds
        r[ins.second] += r[ins.third];
        overflow(r[ins.second]);
        DEBUG_OUT("r%d=%d\n", ins.second, r[ins.second]);
      break;

      case 7: //7ds
        r[ins.second] *= r[ins.third];
        overflow(r[ins.second]);
        DEBUG_OUT("r%d=%d\n", ins.second, r[ins.second]);
      break;

      case 8: //8da
        r[ins.second] = Instruction::to_int(p[r[ins.third]]);
        DEBUG_OUT("r%d=%d\n", ins.second, r[ins.second]);
      break;

      case 9: { //9sa
        p[r[ins.third]] = Instruction::from_int(r[ins.second]);
#ifdef DEBUG
        Instruction & ti = p[r[ins.third]];
        DEBUG_OUT("a[%03d]=%d%d%d(%03d)\n", r[ins.third], ti.first, ti.second, ti.third, r[ins.second]);
#endif
      }
      break;
    }
  }
  return count;
}

int main() {
  int n;
  if (!(cin >> n))
    return false;

  //skip empty line
  string line;
  getline(cin, line);
  getline(cin, line);

  Program p;
  for (int i = 0; i < n; i++) {
    load_program(p);
    int count = run_program(p);
    cout << count << endl;
    if (i != n - 1)
      cout << endl;
  }
  return 0;
}
