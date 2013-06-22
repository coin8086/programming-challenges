#include <iostream>
#include <vector>

#define MAX_N 10000000

using namespace std;

vector<int> primes;

void init() {
  vector<bool> removed(MAX_N + 1);
  primes.reserve(665000); //There are 664579 prime numbers within 10000000
  primes.push_back(2);
  int i = 3;
  for (; i <= MAX_N; i += 2) {
    if (!removed[i]) {
      primes.push_back(i);
      int s = i + i;
      for (; s <= MAX_N; s += i) {
        removed[s] = true;
      }
    }
  }
}

//The index of a prime p in primes array that is the biggest prime not bigger than n.
int index_of_prime(int n) {
  int r = -1;
  int i = 0;
  int j = primes.size();
  while (i != j) {
    int mid = (i + j) / 2;
    if (primes[mid] == n) {
      r = mid;
      break;
    }
    else if (primes[mid] > n) {
      j = mid;
      if (i == j) {
        r = mid - 1;
      }
    }
    else {
      i = mid + 1;
      if (i == j) {
        r = mid;
      }
    }
  }
  return r;
}

inline bool is_prime(int n) {
  return n < 2 ? false : primes[index_of_prime(n)] == n;
}

bool backtrack(int n, int q, vector<int> & a) {
  int r = false;
  if (q == 1) {
    if (is_prime(n)) {
      a.push_back(n);
      r = true;
    }
  }
  else {
    int i = index_of_prime(n);
    q--;
    for (; i >= 0; i--) {
      if (backtrack(n - primes[i], q, a)) {
        a.push_back(primes[i]);
        r = true;
        break;
      }
    }
  }
  return r;
}

inline bool four_primes(int n, vector<int> & a) {
  if (n < 8)
    return false;
  return backtrack(n, 4, a);
}

int main() {
  init();
  int n;
  while (cin >> n) {
    vector<int> a;
    if (four_primes(n, a)) {
      for (int i = 0; i < 4; i++) {
        if (i)
          cout << ' ';
        cout << a[i];
      }
      cout << endl;
    }
    else {
      cout << "Impossible." << endl;
    }
  }
  return 0;
}
