/***********************************************************
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include "bigint.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
  BigInt op1, op2, r;
  char op;
  while (cin >> op1 >> op >> op2) {
    switch (op) {
      case '+':
        r = op1 + op2;
        break;
      case '-':
        r = op1 - op2;
        break;
      case '*':
        r = op1 * op2;
        break;
      case '/':
        r = op1 / op2;
        break;
      case '^':
        r = BigInt::pow(op1, op2.to_int());
        break;
      case '!':
        r = BigInt::fact(op1.to_int());
        break;
    }
    cout << r << endl;
  }
  return 0;
}
