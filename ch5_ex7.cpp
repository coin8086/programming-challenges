/***********************************************************
 * The Stern-Brocot Number System
 * PC/UVa IDs: 110507/10077
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>

using namespace std;

typedef long long llt;

class Fraction {
  friend ostream & operator <<(ostream & os, const Fraction & f) {
    os << "<" << f._n << ", " << f._d << ">";
    return os;
  }

public:
  Fraction(unsigned int a, unsigned int b) : _n(a), _d(b) {}

  Fraction(const Fraction & f) : _n(f._n), _d(f._d) {}

  Fraction & operator =(const Fraction & f) {
    _n = f._n;
    _d = f._d;
    return *this;
  }

  bool operator <(const Fraction & f) const {
    return (llt)_n * f._d - (llt)_d * f._n < 0;
  }

  bool operator !=(const Fraction & f) const {
    return !(_n == f._n && _d == f._d);
  }

  Fraction middle(const Fraction & f) const {
    return Fraction(_n + f._n, _d + f._d);
  }

private:
  unsigned int _n; //numerator
  unsigned int _d; //denominator
};

vector<char> stern_brocot_path(const Fraction & f) {
  vector<char> path;
  Fraction mid(1, 1);
  Fraction left(0, 1);
  Fraction right(1, 0);
  //clog << f << endl;
  while (f != mid) {
    //clog << left << " " << mid << " " << right << endl;
    if (f < mid) {
      right = mid;
      mid = mid.middle(left);
      path.push_back('L');
    }
    else {
      left = mid;
      mid = mid.middle(right);
      path.push_back('R');
    }
  }
  return path;
}

int main() {
  unsigned int a, b;
  while ((cin >> a >> b) && !(a == 1 && b == 1)) {
    vector<char> path = stern_brocot_path(Fraction(a, b));
    for (int i = 0; i < path.size(); i++)
      cout << path[i];
    cout << endl;
  }
  return 0;
}
