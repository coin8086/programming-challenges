/***********************************************************
 * Check the Check
 * PC/UVa IDs: 110107/10196
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>

using namespace std;

typedef char Board[8][8];
typedef struct _Position {
  int row;
  int col;
} Position;

bool load_board(Board & board, Position & k, Position & K) {
  bool empty = true;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      char ch;
      if (!(cin >> ch))
        break;

      if (empty && ch != '.')
        empty = false;

      board[i][j] = ch;

      if (ch == 'k') {
        k.row = i;
        k.col = j;
      }
      else if (ch == 'K') {
        K.row = i;
        K.col = j;
      }
    }
  }
  return !empty;
}

bool check_black(const Board & board, const Position & k) {
  //horizontal check
  for (int i = k.col + 1; i < 8; i++) {
    char ch = board[k.row][i];
    if (ch == '.')
      continue;
    if (ch == 'R' || ch == 'Q')
      return true;
    break;
  }

  for (int i = k.col - 1; i >= 0; i--) {
    char ch = board[k.row][i];
    if (ch == '.')
      continue;
    if (ch == 'R' || ch == 'Q')
      return true;
    break;
  }

  //vertical check
  for (int i = k.row - 1; i >= 0; i--) {
    char ch = board[i][k.col];
    if (ch == '.')
      continue;
    if (ch == 'R' || ch == 'Q')
      return true;
    break;
  }

  for (int i = k.row + 1; i < 8; i++) {
    char ch = board[i][k.col];
    if (ch == '.')
      continue;
    if (ch == 'R' || ch == 'Q')
      return true;
    break;
  }

  //diagonal check
  for (int i = k.row + 1, j = k.col + 1; i < 8 && j < 8; i++, j++) {
    char ch = board[i][j];
    if (ch == '.')
      continue;
    if (ch == 'B' || ch == 'Q' || (ch == 'P' && i == k.row + 1))
      return true;
    break;
  }

  for (int i = k.row + 1, j = k.col - 1; i < 8 && j >= 0; i++, j--) {
    char ch = board[i][j];
    if (ch == '.')
      continue;
    if (ch == 'B' || ch == 'Q' || (ch == 'P' && i == k.row + 1))
      return true;
    break;
  }

  for (int i = k.row - 1, j = k.col - 1; i >= 0 && j >= 0; i--, j--) {
    char ch = board[i][j];
    if (ch == '.')
      continue;
    if (ch == 'B' || ch == 'Q')
      return true;
    break;
  }

  for (int i = k.row - 1, j = k.col + 1; i >= 0 && j < 8; i--, j++) {
    char ch = board[i][j];
    if (ch == '.')
      continue;
    if (ch == 'B' || ch == 'Q')
      return true;
    break;
  }

  //knight check
  Position pos[8];
  pos[0].row = k.row + 1;
  pos[0].col = k.col + 2;

  pos[1].row = k.row + 2;
  pos[1].col = k.col + 1;

  pos[2].row = k.row + 2;
  pos[2].col = k.col - 1;

  pos[3].row = k.row + 1;
  pos[3].col = k.col - 2;

  pos[4].row = k.row - 1;
  pos[4].col = k.col - 2;

  pos[5].row = k.row - 2;
  pos[5].col = k.col - 1;

  pos[6].row = k.row - 2;
  pos[6].col = k.col + 1;

  pos[7].row = k.row - 1;
  pos[7].col = k.col + 2;

  for (int i = 0; i < 8; i++) {
    Position & p = pos[i];
    if (p.row < 8 && p.row >= 0 && p.col < 8 && p.col >= 0
      && board[p.row][p.col] == 'N')
      return true;
  }

  return false;
}

inline char flip_char(char ch) {
  if (ch == '.')
    return ch;
  return ch >= 'a' ? (ch - ('a' - 'A')) : (ch + ('a' - 'A'));
}

void flip_board(Board & board, Position & K) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      char up = board[j][i];
      char down = board[7 - j][i];
      board[j][i] = flip_char(down);
      board[7 - j][i] = flip_char(up);
    }
  }
  K.row = 7 - K.row;
}

int check_board(Board & board, Position & k, Position & K) {
  if (check_black(board, k))
    return 1;
  flip_board(board, K);
  return check_black(board, K) ? 2 : 0;
}

int main() {
  Board board;
  Position k, K;
  int d = 0;
  while (load_board(board, k, K)) {
    int r = check_board(board, k, K);
    const char * who;
    switch (r) {
      case 0:
        who = "no king";
      break;
      case 1:
        who = "black king";
      break;
      case 2:
        who = "white king";
      break;
    }
    cout << "Game #" << ++d << ": " << who << " is in check." << endl;
  }
  return 0;
}
