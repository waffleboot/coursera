#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

struct entry {
  size_t rotation;
  string text;
};

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  vector<int> result (text.size());
  vector<entry> entries (text.size());

  string tmp = text;
  for (size_t i = 0; i < text.size(); ++i) {
    entries[i].text = tmp;
    entries[i].rotation = i;
    rotate(begin(tmp),next(begin(tmp)),end(tmp));
  }
  sort(begin(entries),end(entries),[](auto & e1, auto & e2){
    return e1.text < e2.text;
  });
  for (size_t i = 0; i < text.size(); ++i) {
    result[i] = entries[i].rotation;
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    printf(i ? " %d" : "%d", suffix_array[i]);
  }
  return 0;
}
