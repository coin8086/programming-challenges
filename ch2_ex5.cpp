#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

const char * values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
const char * suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

vector<int> shuffle(const vector<int> & cards, const vector<int> & order) {
  vector<int> r(cards.size());
  for (int i = 0; i < order.size(); i++) {
    r[i] = cards[order[i]];
  }
  return r;
}

void output(const vector<int> & cards) {
  for (int i = 0; i < cards.size(); i++) {
    int v = cards[i] % 13;
    int s = cards[i] / 13;
    cout << values[v] << " of " << suits[s] << endl;
  }
}

int main() {
  string line;
  getline(cin, line);
  int n = atoi(line.c_str());
  getline(cin, line); //skip empty line
  for (int i = 0; i < n; i++) {
    int m = 0;
    cin >> m;
    vector<vector<int> > methods(m);
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < 52; k++) {
        int order;
        cin >> order;
        methods[j].push_back(order - 1);
      }
    }
    getline(cin, line); //skip till a new line
    vector<int> cards(52);
    for (int l = 0; l < cards.size(); l++) {
      cards[l] = l;
    }
    while(getline(cin, line)) {
      if (line.empty())
        break;
      int k = atoi(line.c_str()) - 1;
      cards = shuffle(cards, methods[k]);
    }
    output(cards);
    if (i != n - 1)
      cout << endl;
  }
  return 0;
}
