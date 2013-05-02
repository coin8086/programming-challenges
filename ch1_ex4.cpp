#include <iostream>
#include <vector>
#include <algorithm>

#ifdef DEBUG
#include "../comm_headers/debug_helper.h"
#else
#define DEBUG_OUT(...)
#endif

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matrix;
typedef vector<Matrix> Font;

vector<Font> fonts(10);

char digits[][5][3] = {
  //0
  {
    {' ', '-', ' '},
    {'|', ' ', '|'},
    {' ', ' ', ' '},
    {'|', ' ', '|'},
    {' ', '-', ' '},
  },
  //1
  {
    {' ', ' ', ' '},
    {' ', ' ', '|'},
    {' ', ' ', ' '},
    {' ', ' ', '|'},
    {' ', ' ', ' '},
  },
  //2
  {
    {' ', '-', ' '},
    {' ', ' ', '|'},
    {' ', '-', ' '},
    {'|', ' ', ' '},
    {' ', '-', ' '},
  },
  //3
  {
    {' ', '-', ' '},
    {' ', ' ', '|'},
    {' ', '-', ' '},
    {' ', ' ', '|'},
    {' ', '-', ' '},
  },
  //4
  {
    {' ', ' ', ' '},
    {'|', ' ', '|'},
    {' ', '-', ' '},
    {' ', ' ', '|'},
    {' ', ' ', ' '},
  },
  //5
  {
    {' ', '-', ' '},
    {'|', ' ', ' '},
    {' ', '-', ' '},
    {' ', ' ', '|'},
    {' ', '-', ' '},
  },
  //6
  {
    {' ', '-', ' '},
    {'|', ' ', ' '},
    {' ', '-', ' '},
    {'|', ' ', '|'},
    {' ', '-', ' '},
  },
  //7
  {
    {' ', '-', ' '},
    {' ', ' ', '|'},
    {' ', ' ', ' '},
    {' ', ' ', '|'},
    {' ', ' ', ' '},
  },
  //8
  {
    {' ', '-', ' '},
    {'|', ' ', '|'},
    {' ', '-', ' '},
    {'|', ' ', '|'},
    {' ', '-', ' '},
  },
  //9
  {
    {' ', '-', ' '},
    {'|', ' ', '|'},
    {' ', '-', ' '},
    {' ', ' ', '|'},
    {' ', '-', ' '},
  },
};

vector<int> number_to_digits(int n) {
  vector<int> r;
  if (!n) {
    r.push_back(0);
  }
  else {
    while (n) {
      r.push_back(n % 10);
      n = n / 10;
    }
    reverse(r.begin(), r.end());
  }
  return r;
}

void draw(int n, int s);

void init_fonts() {
  DEBUG_OUT("init_fonts()\n");
  for (int i = 0; i < fonts.size(); i++) {
    fonts[i].resize(10);
  }
  Font & s1 = fonts[0];
  for (int i = 0; i < 10; i++) {
    s1[i].resize(5);
    for (int j = 0; j < 5; j++) {
      s1[i][j].resize(3);
      for (int k = 0; k < 3; k++) {
        s1[i][j][k] = digits[i][j][k];
        DEBUG_OUT("%c", s1[i][j][k]);
      }
      DEBUG_OUT("\n");
    }
    DEBUG_OUT("\n");
  }
}

const Matrix & digit_to_matrix(int d, int s) {
  Matrix & matrix = fonts[s - 1][d];
  if (matrix.size() > 0)
    return matrix;

  Matrix & s1 = fonts[0][d];

  matrix.resize(2 * s + 3);
  for (int i = 0; i < s * 2 + 3; i++) {
    matrix[i].resize(s + 2, ' ');
  }

  //top line
  char ch = s1[0][1];
  if (ch != ' ')
    for (int i = 1; i <= s; i++)
      matrix[0][i] = ch;

  //middle line
  ch = s1[2][1];
  if (ch != ' ')
    for (int i = 1; i <= s; i++)
      matrix[s + 1][i] = ch;

  //bottom line
  ch = s1[4][1];
  if (ch != ' ')
    for (int i = 1; i <= s; i++)
      matrix[2 * s + 2][i] = ch;

  //left up side
  ch = s1[1][0];
  if (ch != ' ')
    for (int i = 1; i <= s; i++)
      matrix[i][0] = ch;

  //left down side
  ch = s1[3][0];
  if (ch != ' ')
    for (int i = 1; i <= s; i++)
      matrix[s + 1 + i][0] = ch;

  //right up side
  ch = s1[1][2];
  if (ch != ' ')
    for (int i = 1; i <= s; i++)
      matrix[i][s + 1] = ch;

  //right down side
  ch = s1[3][2];
  if (ch != ' ')
    for (int i = 1; i <= s; i++)
      matrix[s + 1 + i][s + 1] = ch;

  return matrix;
}

void draw(int n, int s) {
  vector<int> digits = number_to_digits(n);
  for (int r = 0; r < 2 * s + 3; r++) {
    for (int i = 0; i < digits.size(); i++) {
      if (i)
        cout << ' ';

      const Matrix & m = digit_to_matrix(digits[i], s);
      for (int j = 0; j < s + 2; j++) {
        cout << m[r][j];
      }
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  init_fonts();

  int s, n;
  while (cin >> s >> n) {
    DEBUG_OUT("s: %d n: %d\n", s, n);
    if (!s && !n)
      break;

    draw(n, s);
  }
  return 0;
}
