/***********************************************************
 * Australian Voting
 * PC/UVa IDs: 110108/10142
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef vector<int> Voting;
typedef map<int, vector<Voting> > Result;

class Candidate {
public:
  Candidate(int ai, int av) : idx(ai), votes(av) {}
  bool operator <(const Candidate & c) const { return votes > c.votes; }
  int idx;   //index for a candidate
  int votes; //his/her votes
};

inline Result init(const vector<Voting> & votings) {
  Result result;
  for (int i = 0; i < votings.size(); i++) {
    result[votings[i].back()].push_back(votings[i]);
  }
  return result;
}

bool elect(const Result & result, int total, vector<int> & victors,
  vector<int> & losers)
{
  bool over = false;
  victors.clear();
  losers.clear();
  vector<Candidate> cand;
  Result::const_iterator it = result.begin();
  for (; it != result.end(); it++) {
    cand.push_back(Candidate(it->first, it->second.size()));
  }
  sort(cand.begin(), cand.end());
  if (cand[0].votes * 1.0 / total > 0.5) {
    over = true;
    victors.push_back(cand[0].idx);
  }
  else if (cand.front().votes == cand.back().votes) {
    over = true;
    for (int i = 0; i < cand.size(); i++) {
      victors.push_back(cand[i].idx);
    }
  }
  else {
    int v = cand.back().votes;
    losers.push_back(cand.back().idx);
    for (int i = cand.size() - 2; i > 0; i--) {
      if (cand[i].votes == v)
        losers.push_back(cand[i].idx);
    }
  }
  return over;
}

inline bool contain(const vector<int> & vec, int e) {
  return find(vec.begin(), vec.end(), e) != vec.end();
}

void eliminate(Result & result, const vector<int> & losers) {
  for (int i = 0; i < losers.size(); i++) {
    Result::iterator it = result.find(losers[i]);
    vector<Voting> & votings = it->second;
    //Reassign losers' votings to those non-eliminated
    for (int j = 0; j < votings.size(); j++) {
      Voting & v = votings[j];
      v.pop_back();
      while (!result.count(v.back()) || contain(losers, v.back()))
        v.pop_back();
      result[v.back()].push_back(v);
    }
    result.erase(it);
  }
}

inline vector<int> vote(const vector<Voting> & votings) {
  vector<int> victors;
  vector<int> losers;
  Result result = init(votings);
  int total = votings.size();
  while (!elect(result, total, victors, losers)) {
    eliminate(result, losers);
  }
  return victors;
}

int main() {
  int N = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int n;
    cin >> n;
    //Read candidate names
    string line;
    getline(cin, line); //Skip empty line
    vector<string> names(n + 1);
    int j;
    for (j = 1; j <= n; j++) {
      getline(cin, names[j]);
    }
    //Read votings
    vector<Voting> votings;
    votings.reserve(1000);
    getline(cin, line);
    while(!line.empty()) {
      istringstream is(line);
      Voting v;
      v.reserve(n);
      for (int k = 0; k < n; k++) {
        int p;
        is >> p;
        v.push_back(p);
      }
      //The last one has the highest rank, the first one the lowest.
      //This is for efficient removing an eliminated candidate.
      reverse(v.begin(), v.end());
      votings.push_back(v);
      getline(cin, line);
    }
    vector<int> victors = vote(votings);
    if (i)
      cout << endl;
    for (j = 0; j < victors.size(); j++) {
      cout << names[victors[j]] << endl;
    }
  }
  return 0;
}
