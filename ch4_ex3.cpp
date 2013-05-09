#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

inline int cross(vector<vector<int> > & order, int fast, int slow = 0) {
  if (!slow) {
    order.push_back(vector<int>(1, fast));
    return fast;
  }
  vector<int> group(2);
  group[0] = fast;
  group[1] = slow;
  order.push_back(group);
  return slow;
}

int min_time(vector<int> & people, vector<vector<int> > & order) {
  if (people.size() == 1) {
    order.push_back(vector<int>(1, people[0]));
    return people[0];
  }
  sort(people.begin(), people.end());
  int t = 0;
  int p0 = people[0];
  int p1 = people[1];
  while (!people.empty()) {
    int size = people.size();
    if (size == 2) {
      t += cross(order, p0, p1);
      people.clear();
    }
    else if (size == 3) {
      t += cross(order, p0, people[2]);
      t += cross(order, p0);
      t += cross(order, p0, p1);
      people.clear();
    }
    else {
      if (p1 - p0 < people[size - 2] - p1) {
        t += cross(order, p0, p1);
        t += cross(order, p0);
        t += cross(order, people[size - 2], people.back());
        t += cross(order, p1);
        people.pop_back();
        people.pop_back();
      }
      else {
        t += cross(order, p0, people.back());
        t += cross(order, p0);
        people.pop_back();
      }
    }
  }
  return t;
}

int main() {
  int n_case = 0;
  cin >> n_case;
  for (int i = 0; i < n_case; i++) {
    int n = 0;
    cin >> n;
    vector<int> people(n);
    int j;
    for (j = 0; j < n; j++)
      cin >> people[j];
    vector<vector<int> > order;
    int t = min_time(people, order);
    if (i != 0)
      cout << endl;
    cout << t << endl;
    for (j = 0; j < order.size(); j++) {
      for (int k = 0; k < order[j].size(); k++) {
        if (k != 0)
          cout << ' ';
        cout << order[j][k];
      }
      cout << endl;
    }
  }
}
