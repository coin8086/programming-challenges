/***********************************************************
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void backtrack(vector<int> & cols, int k, int & counter) {
  if (cols.size() == k) {
    counter++;
  }
  else {
    vector<int> cand;
    int i;
    for (i = 0; i < cols.size(); i++) {
      bool ok = true;
      for (int j = 0; j < k; j++) {
        if (cols[j] == i || abs(j - k) == abs(cols[j] - i)) {
          ok = false;
          break;
        }
      }
      if (ok)
        cand.push_back(i);
    }
    for (i = 0; i < cand.size(); i++) {
      cols[k] = cand[i];
      backtrack(cols, k + 1, counter);
    }
  }
}

int queens(int n) {
  int counter = 0;
  vector<int> cols(n, -1);
  backtrack(cols, 0, counter);
  return counter;
}

int main(int argc, char ** argv) {
  int n;
  if (argc != 2 || (n = atoi(argv[1])) < 1) {
    cerr << "usage:" << endl;
    cerr << argv[0] << ' ' << "<N>" << endl;
    return 1;
  }
  cout << queens(n) << endl;
  return 0;
}
