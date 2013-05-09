#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> shell_sort(vector<string> & old_order, vector<string> & new_order) {
  vector<string> steps;
  vector<string>::iterator end = old_order.end();
  vector<string>::iterator prev = end;
  for (int i = 0; i < new_order.size() - 1; i++) {
    string & s1 = new_order[i];
    string & s2 = new_order[i + 1];
    vector<string>::iterator it1 = (prev == end ? find(old_order.begin(), end, s1) : prev);
    vector<string>::iterator it2 = find(old_order.begin(), old_order.end(), s2);
    if (it1 > it2) {
      old_order.erase(it2);
      old_order.push_back(s2);
      steps.push_back(s2);
      prev = end - 1;
    }
    else {
      prev = it2;
    }
  }
  return steps;
}

int main() {
  int k = 0;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int n = 0;
    cin >> n;
    string line;
    getline(cin, line); //skip empty line
    int j;
    vector<string> old_order;
    for (j = 0; j < n; j++) {
      getline(cin, line);
      old_order.push_back(line);
    }
    reverse(old_order.begin(), old_order.end());
    vector<string> new_order;
    for (j = 0; j < n; j++) {
      getline(cin, line);
      new_order.push_back(line);
    }
    reverse(new_order.begin(), new_order.end());
    vector<string> steps = shell_sort(old_order, new_order);
    for (j = 0; j < steps.size(); j++) {
      cout << steps[j] << endl;
    }
    cout << endl;
  }
}
