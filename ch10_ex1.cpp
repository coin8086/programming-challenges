/***********************************************************
 * Freckles
 * PC/UVa IDs: 111001/10034
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <limits>
#include <cmath>

using namespace std;

class Point {
public:
  Point() : x(0), y(0) {}

  Point(double ax, double ay) : x(ax), y(ay) {}

  bool operator <(const Point & p) const {
    bool r;
    if (x < p.x)
      r = true;
    else if (x > p.x)
      r = false;
    else {
      if (y < p.y)
        r = true;
      else
        r = false;
    }
    return r;
  }

  double distance(const Point & p) const {
    double dx = x - p.x;
    double dy = y - p.y;
    return sqrt(dx * dx + dy * dy);
  }

  double x;
  double y;
};

typedef vector<Point> Graph;

double mst(const Graph & g) {
  double r = 0;
  map<Point, bool> intree;
  map<Point, double> dist;
  map<Point, Point> pred;
  for (int i = 0; i < g.size(); i++) {
    dist[g[i]] = numeric_limits<double>::max();
  }
  const Point * p = &g[0];
  while (p) {
    intree[*p] = true;
    const Point * np = 0;
    double min = numeric_limits<double>::max();
/************************************************************
    unoptimized code snippet:

    for (int i = 0; i < g.size(); i++) {
      if (intree.find(g[i]) == intree.end()) {
        double d = p->distance(g[i]);
        map<Point, double>::iterator it = dist.find(g[i]);
        if (d < it->second) {
          it->second = d;
          pred[g[i]] = *p;
        }
        if (it->second < min) {
          min = it->second;
          np = &g[i];
        }
      }
    }
************************************************************/
    map<Point, double>::iterator it = dist.begin();
    for (; it != dist.end(); it++) {
      const Point & p2 = it->first;
      if (intree.find(p2) == intree.end()) { //use find to avoid adding p2 to intree if not yet
        double d = p->distance(p2);
        if (d < it->second) {
          it->second = d;
          pred[p2] = *p;
        }
        if (it->second < min) {
          min = it->second;
          np = &p2; //It doesn't matter np(then passed to p) points to inside of dist rather than g;
        }
      }
    }
    p = np;
  }
  map<Point, Point>::iterator it = pred.begin();
  for (; it != pred.end(); it++) {
    r += it->first.distance(it->second);
  }
  return r;
}

int main() {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    Graph g;
    int nv = 0;
    cin >> nv;
    for (int j = 0; j < nv; j++) {
      double x, y;
      cin >> x >> y;
      g.push_back(Point(x, y));
    }
    if (i) {
      cout << endl;
    }
    cout << fixed << setprecision(2) << mst(g) << endl;
  }
  return 0;
}
