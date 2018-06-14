#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <array>

using std::cin;
using std::cout;
using std::endl;
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

std::array<size_t,5> MakeFirstColumnOffsets(const string& text) {
  std::array<size_t,5> count {};
  for (auto c : text) {
    ++count[LetterToIndex(c)];
  }
  std::array<size_t,5> offset {};
  for (size_t i = 1; i < count.size(); ++i) {
    offset[i] = count[i-1];
    count[i] += count[i-1];
  }
  return offset;
}

vector<size_t> MakeLastColumnOffsets(const string& text) {
  std::array<size_t,5> count {};
  vector<size_t> offset (text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    offset[i] = count[LetterToIndex(text[i])]++;
  }
  return offset;
}

string InverseBWT(const string& bwt) {
  string text (bwt.size(),'$');
  
  auto firstColumnOffsets = MakeFirstColumnOffsets(bwt);
  auto lastColumnOffsets  = MakeLastColumnOffsets(bwt);
  
  size_t pos = 0;
  size_t index = bwt.size()-1;
  do {
    auto ch = text[--index] = bwt[pos];
    pos = firstColumnOffsets[LetterToIndex(ch)] + lastColumnOffsets[pos];
  } while (pos > 0);

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
//  cout << InverseBWT(bwt);
  printf("%s", InverseBWT(bwt).c_str());
  return 0;
}
