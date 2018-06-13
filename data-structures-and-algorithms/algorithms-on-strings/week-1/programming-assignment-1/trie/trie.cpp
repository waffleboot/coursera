#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(const vector<string> & patterns) {

    trie t (1);

    for (auto & pattern : patterns) {
        size_t pos = 0;
        for (auto ch : pattern) {
            auto & m = t[pos];
            auto search = m.find(ch);
            if (search != m.cend()) {
                pos = search->second;
            } else {
                pos = t.size();
                m.insert({ch,pos});
                t.push_back({});
            }
        }
    }
    
    return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
