#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

typedef vector<string> Line;

string known_line = "the quick brown fox jumps over the lazy dog";
Line known;

inline Line break_down(const string & line) {
  Line words;
  string word;
  istringstream is(line);
  while (is >> word) {
    words.push_back(word);
  }
  return words;
}

inline void init() {
  known = break_down(known_line);
}

bool match_word(const string & enc, const string & known, vector<char> & alphabet) {
  if (enc.size() != known.size())
    return false;
  vector<char> alpha = alphabet;
  for (int i = 0; i < enc.size(); i++) {
    int idx = enc[i] - 'a';
    if (alpha[idx]) {
      if (alpha[idx] != known[i]) {
        return false;
      }
    }
    else {
      alpha[idx] = known[i];
    }
  }
  vector<bool> map(alpha.size(), false);
  for (int i = 0; i < alpha.size(); i++) {
    if (alpha[i]) {
      int idx = alpha[i] - 'a';
      if (!map[idx])
        map[idx] = true;
      else
        return false;
    }
  }
  alphabet = alpha;
  return true;
}

bool match_line(const Line & encrypted, vector<char> & alphabet) {
  if (encrypted.size() != known.size())
    return false;
  vector<char> alpha(26);
  for (int i = 0; i < encrypted.size(); i++) {
    if (!match_word(encrypted[i], known[i], alpha))
      return false;
  }
  alphabet = alpha;
  return true;
}

inline bool decrypt(const vector<string> & lines, vector<char> & alphabet) {
  for (int i = 0; i < lines.size(); i++) {
    if (match_line(break_down(lines[i]), alphabet))
      return true;
  }
  return false;
}

inline string translate(const string & line, const vector<char> & alphabet) {
  string r(line);
  for (int i = 0; i < r.size(); i++) {
    if (r[i] != ' ')
      r[i] = alphabet[r[i] - 'a'];
  }
  return r;
}

int main() {
  init();
  string line;
  getline(cin, line);
  int n_test = atoi(line.c_str());
  getline(cin, line); //skip empty line
  for (int i = 0; i < n_test; i++) {
    vector<string> lines;
    while (getline(cin, line) && !line.empty()) {
      lines.push_back(line);
    }
    vector<char> alphabet(26);
    if (decrypt(lines, alphabet)) {
      for (int j = 0; j < lines.size(); j++) {
        cout << translate(lines[j], alphabet) << endl;
      }
    }
    else {
      cout << "No solution." << endl;
    }
    if (i != n_test - 1)
      cout << endl;
  }
}