/***********************************************************
 * Slash Maze
 * PC/UVa IDs: 110904/705
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

typedef pair<int, int> Point;

typedef map<Point, vector<Point> > Grid;

typedef vector<vector<char> > Maze;

/*
 * Rotate the Maze conter-clockwise for 45 degrees to get a grid system. Each
 * slash means connection of two pairs of grid points. This function translate
 * the Slash Maze to a graph of the grid system.
 * */
Grid mazeToGrid(const Maze & m) {
  Grid g;
  int i = 0, j = 0; //Grid coordinates
  int x, y;         //Maze coordinates
  int h = m.size();
  int w = m[0].size();
  //Initially, let m(0, 0) corresponds to g(0, 0). This may cause negative i/j
  //for a grid, but it doesn't matter, since grid g is a adjacency list.
  for (x = 0; x < h; x++) {
    int oi = i;
    int oj = j;
    for (y = 0; y < w; y++) {
      //m(x, y) corresponds to g(i, j) that is the top grid of the four grids
      //that slash m(x, y) involves.
      if (m[x][y] == '\\') {
        //Then top and right grids connect, so do left and bottom grids.
        g[Point(i, j)].push_back(Point(i, j + 1));
        g[Point(i, j + 1)].push_back(Point(i, j));
        g[Point(i + 1, j)].push_back(Point(i + 1, j + 1));
        g[Point(i + 1, j + 1)].push_back(Point(i + 1, j));
      }
      else {
        //Then top and left grids connect, so do right and bottom grids.
        g[Point(i, j)].push_back(Point(i + 1, j));
        g[Point(i + 1, j)].push_back(Point(i, j));
        g[Point(i, j + 1)].push_back(Point(i + 1, j + 1));
        g[Point(i + 1, j + 1)].push_back(Point(i, j + 1));
      }
      //while m(x, y) corresponds to g(i, j), m(x, y + 1) corresponds to
      //g(i - 1, j + 1)
      i--;
      j++;
    }
    //while m(x, y) corresponds to g(i, j), m(x + 1, y) corresponds to
    //g(i + 1, j + 1)
    i = oi + 1;
    j = oj + 1;
  }
  return g;
}

void dfs(const Grid & g, const Point & v, const Point & s,
    set<Point> & visited, map<Point, Point> & pred) {
  visited.insert(v);
  const vector<Point> & neighbours = g.find(v)->second;
  assert(neighbours.size() <= 2);
  for (int i = 0; i < neighbours.size(); i++) {
    const Point & n = neighbours[i];
    if (!visited.count(n)) {
      pred[n] = v;
      dfs(g, n, s, visited, pred);
    }
    else if (n == s && pred[v] != s) {
      pred[s] = v; //A cycle is detected!
    }
  }
}

vector<int> cycles(const Grid & g) {
  set<Point> visited;
  vector<int> cycles;
  for (Grid::const_iterator it = g.begin(); it != g.end(); ++it) {
    if (!visited.count(it->first)) {
      map<Point, Point> pred;
      dfs(g, it->first, it->first, visited, pred);
      //If a start point has a predecessor, it means a cycle.
      if (pred.count(it->first)) {
        cycles.push_back(pred.size());
      }
    }
  }
  return cycles;
}

void solve(const Maze & m, int i) {
  Grid g = mazeToGrid(m);
  vector<int> res = cycles(g);
  cout << "Maze #" << i << ":" << endl;
  if (res.size() > 0) {
    int max = *max_element(res.begin(), res.end());
    cout << res.size() << " Cycles; the longest has length " << max << "." << endl;
  }
  else {
    cout << "There are no cycles." << endl;
  }
  cout << endl;
}

int main() {
  int n = 1;
  while(true) {
    int w, h;
    cin >> w >> h;
    if (w == 0 && h == 0)
      break;
    Maze m(h);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        char ch;
        cin >> ch;
        m[i].push_back(ch);
      }
    }
    solve(m, n++);
  }
  return 0;
}
