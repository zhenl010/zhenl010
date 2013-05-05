#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

template <typename T, int N>
int ArraySize(const T (&a) [N]) { return N; }

class Solution {
 public:
  vector<string> fullJustify(vector<string> &words, int L) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<string> result;
    vector<string> line;
    int line_length = 0;
    for (size_t i=0; i<words.size(); ++i) {
      if (words[i].empty()) {
        continue; // skip empty string
      } else if (line.empty()) {
        line = vector<string>(1, words[i]);
        line_length = words[i].size();
      } else if (line_length+words[i].size()+1 <= L) {
        line.push_back(words[i]);
        line_length += words[i].size()+1;
      } else {
        result.push_back(GetLineStringFull(line, line_length, L));
        line = vector<string>(1, words[i]);
        line_length = words[i].size();
      }
    }

    if (!line.empty()) {
      result.push_back(GetLineStringLeft(line, line_length, L));
    }

    return result.empty() ? vector<string>(1, string(L, ' ')) : result;
  }

 private:
   // assemble justified line from words where line_length is calculated as
   // sum(word lengths) + (number of words)
  string GetLineStringFull(const vector<string> &line,
                           int line_length, int L) {
    assert(!line.empty());
    string str = line[0];
    // special case to avoid divide by zero case
    if (line.size()==1) return str + string(L-str.size(), ' ');

    int long_space_num = (L-line_length) % (line.size()-1);
    string delim(1+(L-line_length) / ((line.size()-1)), ' ');
    for (size_t i=1; i<line.size(); ++i) {
      if ((i-1)<long_space_num) {
        str += (" " + delim + line[i]);
      } else {
        str += delim + line[i];
      }
    }
    return str;
  }

  // assemble justified line from words where line_length is calculated as
  // sum(word lengths) + (number of words)
  string GetLineStringLeft(const vector<string> &line, int line_length, int L) {
    assert(!line.empty());
    string str = line[0];
    for (size_t i=1; i<line.size(); ++i) {
      str += (" " + line[i]);
    }
    return str + string(L-str.size(), ' ');
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Solution solver;

  // int line_max = 0;
  // int line_max = 1;
  // int line_max = 3;
  // int line_max = 12;
  // int line_max = 6;
  int line_max = 16;
  string word_array[] = {
    // ""
    // "a"
    // "a","b","c","d","e"
    // "What","must","be","shall","be."
    // "Listen","to","many,","speak","to","a","few."
    "Here","is","an","example","of","text","justification."
  };

  vector<string> words(word_array, word_array+ArraySize(word_array));

  vector<string> article = solver.fullJustify(words, line_max);

  return 0;
}