/***********************************************************
 * Shoemaker's Problem
 * PC/UVa IDs: 110405/10026
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Order {
public:
  Order(int i, int t, int s) : _i(i), _t(t), _s(s) {}

  bool operator <(const Order & o) const {
    int m1 = _t * o._s;
    int m2 = o._t * _s;
    return m1 < m2 ? true : (m1 == m2 ? _i < o._i : false);
  }

  int idx() const { return _i; }

  static bool cmp(const Order * p1, const Order * p2) {
    return *p1 < *p2;
  }

private:
  int _i;
  int _t;
  int _s;
};

int main() {
  int N = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int n;
    cin >> n;
    vector<Order> orders;
    vector<Order *> p;
    orders.reserve(n);
    p.reserve(n);
    for (int j = 1; j <= n; j++) {
      int t, s;
      cin >> t >> s;
      orders.push_back(Order(j, t, s));
      p.push_back(&orders.back());
    }
    sort(p.begin(), p.end(), Order::cmp);
    if (i)
      cout << endl;
    for (int k = 0; k < n; k++) {
      if (k)
        cout << ' ';
      cout << p[k]->idx();
    }
    cout << endl;
  }
  return 0;
}
