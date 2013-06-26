/***********************************************************
 * A Multiplication Game
 * PC/UVa IDs: 110505/847
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <cmath>

using namespace std;

bool stan_win(unsigned int n) {
  bool stan = true;
  if (n > 9) {
    //To ensure Stan's success, Ollie's multiplication result must be in
    //[lower, upper).
    unsigned int upper = n;
    unsigned int lower = ceil(n / 9.0);
    stan = !stan; //Indicate the current range is not Stan's.
    while (true) {
      //clog << (stan ? "Stan (" : "Ollie (") << upper << ", " << lower << "]" << endl;
      if (stan && lower <= 9) {
        if (!(lower >= 2 && upper > lower))
          stan = false;
          //clog << (stan ? "Stan wins." : "Ollie wins.") << endl << endl;
        break;
      }
      stan = !stan;
      if (stan) {
        //Stan must ensure no matter which number(x) Ollie chooses, x * p
        //is in desired range. p is Stan's multiplication result.
        upper = ceil(upper / 9.0);
        lower = ceil(lower / 2.0);
      }
      else {
        //Stan must ensure there is a number(x) so that x * p is in desired
        //range. p is Ollie's multiplication result.
        upper = ceil(upper / 2.0);
        lower = ceil(lower / 9.0);
      }
    }
  }
  return stan;
}

int main() {
  unsigned int n;
  while (cin >> n) {
    cout << (stan_win(n) ? "Stan wins." : "Ollie wins.") << endl;
  }
  return 0;
}
