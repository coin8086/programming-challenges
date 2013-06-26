/***********************************************************
 * 15-Puzzle Problem
 * PC/UVa IDs: 110802/10181
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

typedef vector<int> Board;

#ifdef DEBUG
#include <string>

void output_board(const Board & b, int depth) {
  string sp(depth * 2, ' ');
  for (int i = 0; i < 4; i++) {
    cerr << sp;
    for (int j = 0; j < 4; j++) {
      if (j)
        cerr << ' ';
      cerr << b[i * 4 + j];
    }
    cerr << endl;
  }
}

#else
#define output_board(b, d) ((void)(0))
#endif

inline bool is_target(const Board & board) {
  for (int i = 0; i < board.size() - 1; i++) {
    if (board[i] != i + 1)
      return false;
  }
  return true;
}

Board move(const Board & board, char step, int tip = 0) {
  int i;
  if (!board[tip]) {
    i = tip;
  }
  else {
    for (i = 0; i < board.size(); i++) {
      if (!board[i])
        break;
    }
  }
  assert(i != board.size());
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

vector<char> candidates(const Board & board, set<Board> & searched) {
  int i;
  for (i = 0; i < board.size(); i++) {
    if (!board[i])
      break;
  }
  assert(i != board.size());
  int row = i / 4;
  int col = i % 4;
  vector<char> cand;
  if (row != 0 && searched.insert(move(board, 'U', i)).second)
    cand.push_back('U');
  if (row != 3 && searched.insert(move(board, 'D', i)).second)
    cand.push_back('D');
  if (col != 0 && searched.insert(move(board, 'L', i)).second)
    cand.push_back('L');
  if (col != 3 && searched.insert(move(board, 'R', i)).second)
    cand.push_back('R');
  return cand;
}

bool backtrack(Board & board, vector<char> & steps, set<Board> & searched) {
  output_board(board, steps.size());
  if (is_target(board))
    return true;
  if (steps.size() >= 50)
    return false;
  vector<char> cand = candidates(board, searched);
  for (int i = 0; i < cand.size(); i++) {
    steps.push_back(cand[i]);
    Board next = move(board, cand[i]);
    if (backtrack(next, steps, searched))
      return true;
    steps.pop_back();
  }
  return false;
}

bool solve(Board & board, vector<char> & steps) {
  set<Board> searched;
  searched.insert(board);
  return backtrack(board, steps, searched);
}

int main() {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    Board board(16);
    for (int j = 0; j < 16; j++) {
      cin >> board[j];
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
