#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

vector<size_t> ComputePrefixFunction(const string& p) {
  size_t border = 0;
  vector<size_t> s (p.size());
  for (size_t i = 1; i < p.size(); ++i) {
    auto c = p[i];
    while ((border > 0) && c != p[border]) border = s[border-1];
    s[i] = (c == p[border]) ? ++border : 0;
  }
  return s;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  string S; S.reserve(pattern.size() + 1 + text.size());
  S += pattern;
  S += '$';
  S += text;
  auto s = ComputePrefixFunction(S);
  for (size_t i = 2*pattern.size(); i < S.size(); ++i) {
    if (s[i] == pattern.size()) {
      result.push_back(i - 2*pattern.size());
    }
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  return 0;
}
