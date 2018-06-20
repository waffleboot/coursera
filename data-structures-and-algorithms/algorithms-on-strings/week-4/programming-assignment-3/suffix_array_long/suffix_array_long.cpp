#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <array>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using std::array;

size_t LettersToIndex(char c) {
  const static char letters[] = {'$','A','C','G','T'};
  for (size_t i = 0; i < sizeof(letters); ++i) {
    if (letters[i] == c) return i;
  }
  return 0;
}

vector<size_t> SortCharacters(const string& S) {
  array<size_t, 5> count {};
  for (auto c : S) {
    ++count[LettersToIndex(c)];
  }
  for (size_t i = 1; i < count.size(); ++i) {
    count[i] += count[i-1];
  }
  vector<size_t> order (S.size());
  for (size_t i = S.size(); i > 0; --i) {
    auto c = S[i-1];
    order[--count[LettersToIndex(c)]] = i-1;
  }
  return order;
}

vector<size_t> ComputeCharClasses(const string& S, const vector<size_t>& order) {
  vector<size_t> klass (S.size());
  klass[order[0]] = 0;
  for (size_t i = 1; i < S.size(); ++i) {
    if (S[order[i]] != S[order[i-1]]) {
      klass[order[i]] = klass[order[i-1]] + 1;
    } else {
      klass[order[i]] = klass[order[i-1]];
    }
  }
  return klass;
}

vector<size_t> SortedDoubled(const string& S, size_t L, const vector<size_t>& order, const vector<size_t>& klass) {
  vector<size_t> count (S.size());
  for (auto k : klass) {
    ++count[k];
  }
  for (size_t i = 1; i < S.size(); ++i) {
    count[i] += count[i-1];
  }
  vector<size_t> newOrder (S.size());
  for (size_t i = S.size(); i > 0; --i) {
    auto start = (order[i-1] - L + S.size()) % S.size();
    auto k = klass[start];
    newOrder[--count[k]] = start;
  }
  return newOrder;
}

vector<size_t> UpdateClasses(const vector<size_t>& newOrder, const vector<size_t>& klass, size_t L) {
  auto n = newOrder.size();
  vector<size_t> newClass (n);
  newClass[newOrder[0]] = 0;
  for (size_t i = 1; i < n; ++i) {
    auto cur = newOrder[i];
    auto mid = (cur + L) % n;
    auto prev = newOrder[i-1];
    auto midPrev = (prev + L) % n;
    if (klass[cur] != klass[prev] || klass[mid] != klass[midPrev]) {
      newClass[cur] = newClass[prev] + 1;
    } else {
      newClass[cur] = newClass[prev];
    }
  }
  return newClass;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<size_t> BuildSuffixArray(const string& S) {
  auto order = SortCharacters(S);
  auto klass = ComputeCharClasses(S, order);
  for (size_t L = 1; L < S.size(); L <<= 1) {
    order = SortedDoubled(S, L, order, klass);
    klass = UpdateClasses(order, klass, L);
  }
  return order;
}

int main() {
  string text;
  cin >> text;
  auto suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
