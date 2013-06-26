/***********************************************************
 * Crypt Kicker
 * PC/UVa IDs: 110204/843
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#ifdef DEBUG
  #include "../comm_headers/debug_helper.h"
#else
  #define DEBUG_OUT(...) ((void)0)
#endif

using namespace std;

typedef vector<vector<string> > Dict;

class WordComparer {
public:
  WordComparer(const map<string, int> & score) : m_score(score) {}
  bool operator() (const string & a, const string & b) {
    return m_score.at(a) < m_score.at(b); //Because operator [] has no const counterpart so we have to use at() here.
  }
private:
  const map<string, int> & m_score;
};

vector<string> & order(vector<string> & enc) {
  vector<int> alphabet(26, 0);
  for (int i = 0; i < enc.size(); i++) {
    for (int j = 0; j < enc[i].size(); j++) {
      alphabet[enc[i][j] - 'a']++;
    }
  }
  map<string, int> score;
  for (int i = 0; i < enc.size(); i++) {
    int s = 0;
    for (int j = 0; j < enc[i].size(); j++) {
      s += alphabet[enc[i][j] - 'a'];
    }
    score[enc[i]] = s;
  }
  WordComparer cmp(score);
  sort(enc.begin(), enc.end(), cmp);
  return enc;
}

bool guess(const string & w, const string & dw, vector<char> & alphabet) {
  for (int i = 0; i < w.size(); i++) {
    int idx = w[i] - 'a';
    if (alphabet[idx]) {
      if (alphabet[idx] != dw[i]) {
        return false;
      }
    }
    else {
      alphabet[idx] = dw[i];
    }
  }
  vector<bool> map(alphabet.size(), false);
  for (int i = 0; i < alphabet.size(); i++) {
    if (alphabet[i]) {
      int idx = alphabet[i] - 'a';
      if (!map[idx])
        map[idx] = true;
      else
        return false;
    }
  }
  return true;
}

bool decrypt(const Dict & dict, vector<string> & enc, vector<char> & alphabet, int level = 0) {
  if (enc.empty())
    return true;

  string w = enc.back();
  DEBUG_OUT("%*sSELECT %s\n", level * 2, level ? " " : "", w.c_str());

  const vector<string> & cand = dict[w.size()];
  for (int i = 0; i < cand.size(); i++) {
    vector<char> new_alphabet = alphabet;
    if (guess(w, cand[i], new_alphabet)) {
      DEBUG_OUT("%*sTRY %s\n", level * 2, level ? " " : "", cand[i].c_str());
      enc.pop_back();
      if (!decrypt(dict, enc, new_alphabet, level + 1)) {
        enc.push_back(w);
      }
      else {
        alphabet = new_alphabet;
        return true;
      }
    }
  }
  return false;
}

string translate(const string & line, const vector<char> & alphabet) {
  string r(line);
  for (int i = 0; i < r.size(); i++) {
    if (r[i] != ' ')
      r[i] = alphabet[r[i] - 'a'];
  }
  return r;
}

string asterisk(const string & line) {
  string r(line);
  for (int i = 0; i < r.size(); i++) {
    if (r[i] != ' ')
      r[i] = '*';
  }
  return r;
}

int main() {
  int n;
  cin >> n;
  Dict dict(17);
  for (int i = 0; i < n; i++) {
    string word;
    cin >> word;
    dict[word.size()].push_back(word);
  }
  string line;
  getline(cin, line); //skip '\n' just after the last word
  while (getline(cin, line)) {
    if (line.size() == 0)
      break;
    istringstream is(line);
    vector<string> enc;
    string word;
    while (is >> word) {
      enc.push_back(word);
    }
    vector<char> alphabet(26);
    if (decrypt(dict, order(enc), alphabet))
      cout << translate(line, alphabet) << endl;
    else
      cout << asterisk(line) << endl;
  }
  return 0;
}
