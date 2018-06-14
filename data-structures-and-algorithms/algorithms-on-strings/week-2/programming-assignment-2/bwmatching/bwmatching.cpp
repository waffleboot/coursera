#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <array>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

size_t LetterToIndex(char ch) {
  switch (ch) {
    case '$': return 0;
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
  }
}

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  std::array<size_t,5> count {};
  vector<size_t> occ (count.size());
  vector<int> occ_0,occ_1,occ_2,occ_3,occ_4;
  for (auto c : bwt) {
    ++count[LetterToIndex(c)];
    occ_0.push_back(occ[LetterToIndex('$')]);
    occ_1.push_back(occ[LetterToIndex('A')]);
    occ_2.push_back(occ[LetterToIndex('C')]);
    occ_3.push_back(occ[LetterToIndex('G')]);
    occ_4.push_back(occ[LetterToIndex('T')]);
    ++occ[LetterToIndex(c)];
  }
  occ_0.push_back(occ[LetterToIndex('$')]);
  occ_1.push_back(occ[LetterToIndex('A')]);
  occ_2.push_back(occ[LetterToIndex('C')]);
  occ_3.push_back(occ[LetterToIndex('G')]);
  occ_4.push_back(occ[LetterToIndex('T')]);
  
  occ_count_before.emplace('$',std::move(occ_0));
  occ_count_before.emplace('A',std::move(occ_1));
  occ_count_before.emplace('C',std::move(occ_2));
  occ_count_before.emplace('G',std::move(occ_3));
  occ_count_before.emplace('T',std::move(occ_4));

  starts.emplace('A',count[0]); count[1] += count[0];
  starts.emplace('C',count[1]); count[2] += count[1];
  starts.emplace('G',count[2]); count[3] += count[2];
  starts.emplace('T',count[3]);

//  for (size_t i = 0; i <= bwt.size(); ++i) {
//    printf("%d: %d %d %d %d %d\n",
//           i,
//           occ_count_before['$'][i],
//           occ_count_before['A'][i],
//           occ_count_before['C'][i],
//           occ_count_before['G'][i],
//           occ_count_before['T'][i]);
//  }
//  printf("\n");
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const map<char, int>& starts, 
                     const map<char, vector<int> >& occ_count_before) {
  size_t top = 0;
  size_t bottom = bwt.size() - 1;
  size_t pattern_size = pattern.size();
  while (top <= bottom && pattern_size > 0) {
    auto c = pattern[--pattern_size];
    top = starts.at(c) + occ_count_before.at(c)[top];
    bottom = starts.at(c) + occ_count_before.at(c)[bottom+1] - 1;
  }
  return bottom - top + 1;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf(pi ? " %d" : "%d", occ_count);
  }
//  printf("\n");
  return 0;
}
