#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <array>

using std::cin;
using std::string;
using std::vector;
using std::array;
using std::pair;

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

vector<size_t> BuildSuffixArray(const string& S) {
  auto order = SortCharacters(S);
  auto klass = ComputeCharClasses(S, order);
  for (size_t L = 1; L < S.size(); L <<= 1) {
    order = SortedDoubled(S, L, order, klass);
    klass = UpdateClasses(order, klass, L);
  }
  return order;
}

vector<int> FindOccurrences(const string& pattern, const string& text, const vector<size_t>& suffix_array) {
  vector<int> result;
  size_t left  = 0;
  size_t right = suffix_array.size()-1;
  while (left <= right) {
    auto mid = left + (right - left) / 2;
    auto res = strncmp(pattern.c_str(), text.c_str() + suffix_array[mid],pattern.size());
    if (res == 0) {
      size_t i = mid;
      while (i > 0 && strncmp(pattern.c_str(), text.c_str() + suffix_array[i-1],pattern.size()) == 0) --i;
      size_t j = mid;
      while (j+1 < suffix_array.size() && strncmp(pattern.c_str(), text.c_str() + suffix_array[j+1],pattern.size()) == 0) ++j;

      while (i <= j) {
        result.push_back(suffix_array[i]);
        ++i;
      }
      return result;
    }
    if (res < 0) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  auto suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
