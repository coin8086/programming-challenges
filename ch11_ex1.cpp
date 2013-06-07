#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Elephant {
public:
  Elephant() {}

  Elephant(int aw, int as, int ai) : w(aw), s(as), i(ai) {}

  bool operator <(const Elephant & e) const {
    return w < e.w;
  }

  int w;  //weight
  int s;  //smartness
  int i;  //order
};

class Result {
public:
  Result() : max(0), next(0) {}

  bool operator <(const Result & r) const {
    return max < r.max;
  }

  int max;  //max number of elephant in seq
  int next; //next elephant number in seq
};

vector<int> max_seq(vector<Elephant> & ele) {
  int n = ele.size();
  vector<Result> results(n);
  sort(ele.begin(), ele.end());
  results[n - 1].max = 1;
  for (int i = n - 2; i >= 0; i--) {
    Elephant & e = ele[i];
    int max = 0;
    int maxi = 0;
    for (int k = i + 1; k < n; k++) {
      Elephant & e2 = ele[k];
      if (e.w < e2.w && e.s > e2.s && max < results[k].max) {
        max = results[k].max;
        maxi = k;
      }
    }
    results[i].max = max + 1;
    results[i].next = maxi;
  }
  //build path
  vector<Result>::iterator it = max_element(results.begin(), results.end());
  int next = it->next;
  vector<int> r;
  r.push_back(ele[it - results.begin()].i);
  while (next) {
    r.push_back(ele[next].i);
    next = results[next].next;
  }
  return r;
}

int main() {
  int w, s;
  int c = 0;
  vector<Elephant> ele;
  while (cin >> w >> s) {
    ele.push_back(Elephant(w, s, ++c));
  }
  vector<int> seq = max_seq(ele);
  cout << seq.size() << endl;
  for (int i = 0; i < seq.size(); i++)
    cout << seq[i] << endl;
  return 0;
}
