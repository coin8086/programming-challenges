#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef DEBUG
#include "../comm_headers/debug_helper.h"
#else
#define DEBUG_OUT(...)
#endif

using namespace std;

typedef int Program[1000];

void load_program(Program & p) {
  char line[32];
  int i = 0;
  memset(p, 0, sizeof(Program));
  while (fgets(line, 8, stdin)) {
    if (line[0] == '\n')
      break;
    line[3] = 0;
    p[i++] = atoi(line);
  }
}

int run_program(Program & p) {
  int r[10];
  int i = 0;
  bool halt = false;
  int count = 0;

  memset(r, 0, sizeof(int) * 10);
  while (!halt) {
    int ins = p[i++];
    int first = ins / 100;
    int remainder = ins % 100;
    int second = remainder / 10;
    int third = remainder % 10;
    count++;

    DEBUG_OUT("[%03d]%d%d%d: ", i - 1, first, second, third);

    switch (first) {
      case 0: //0ds
        DEBUG_OUT("r%d(%d)?\n", third, r[third]);
        if (r[third]) {
          i = r[second];
          DEBUG_OUT("... goto [%03d]\n", i);
        }
      break;

      case 1:
        halt = true;
        DEBUG_OUT("halt\n");
      break;

      case 2: //2dn
        r[second] = third;
        DEBUG_OUT("r%d=%d\n", second, r[second]);
      break;

      case 3: //3dn
        r[second] = (r[second] + third) % 1000;
        DEBUG_OUT("r%d=%d\n", second, r[second]);
      break;

      case 4: //4dn
        r[second] = (r[second] * third) % 1000;
        DEBUG_OUT("r%d=%d\n", second, r[second]);
      break;

      case 5: //5ds
        r[second] = r[third];
        DEBUG_OUT("r%d=%d\n", second, r[second]);
      break;

      case 6: //6ds
        r[second] = (r[second] + r[third]) % 1000;
        DEBUG_OUT("r%d=%d\n", second, r[second]);
      break;

      case 7: //7ds
        r[second] = (r[second] * r[third]) % 1000;
        DEBUG_OUT("r%d=%d\n", second, r[second]);
      break;

      case 8: //8da
        r[second] = p[r[third]];
        DEBUG_OUT("r%d=%d\n", second, r[second]);
      break;

      case 9: //9sa
        p[r[third]] = r[second];
        DEBUG_OUT("a[%03d]=%03d\n", r[third], r[second]);
      break;
    }
  }
  return count;
}

int main() {
  char line[32];
  int n;
  if (!fgets(line, 32, stdin))
    return false;
  n = atoi(line);
  fgets(line, 32, stdin); //skip empty line

  Program p;
  for (int i = 0; i < n; i++) {
    load_program(p);
    int count = run_program(p);
    printf("%d\n", count);
    if (i != n - 1)
      printf("\n");
  }
  return 0;
}