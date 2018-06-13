#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = text;
  
  vector<string> m (text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    std::rotate(begin(result),next(begin(result)),end(result));
    m[i] = result;
  }
  sort(begin(m),end(m));
  for (size_t i = 0; i < text.size(); ++i) {
    result[i] = m[i].back();
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text);
  return 0;
}
