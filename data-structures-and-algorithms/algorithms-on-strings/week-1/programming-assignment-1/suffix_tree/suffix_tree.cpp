#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

struct edge {
    size_t start;
    size_t length;
    edge(size_t start, size_t length) : start(start), length(length) {}
    vector<edge> children;
};

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.

void add(const string& text, const edge& e, vector<string>& result) {
    result.push_back(text.substr(e.start,e.length));
    for (auto & e : e.children) {
        add(text,e,result);
    }
}

vector<string> ComputeSuffixTreeEdges(const string& text) {

    vector<string> result;

    vector<edge> root_edges;
    for (size_t i = 0; i < text.size(); ++i) {

        auto edges = &root_edges;
        auto suffix_size = text.size() - i;
        auto j = i;
        
        for (;;) {
            auto root_edge = find_if(begin(*edges),end(*edges),[&text,j](const edge & e){
                return text[j] == text[e.start];
            });
            if (root_edge != end(*edges)) {

                size_t length;
                for (length = 0; length < std::min(root_edge->length,suffix_size) && text[j+length] == text[root_edge->start+length]; ++length);

                if (length < root_edge->length) {
                    
                    edge e { root_edge->start + length, root_edge->length - length };
                    swap(e.children,root_edge->children);

                    root_edge->length = length;

                    root_edge->children.push_back(std::move(e));
                    root_edge->children.emplace_back(j+length,suffix_size-length);
                    
                    break;
                    
                } else {
                    j += length;
                    suffix_size -= length;
                    edges = &root_edge->children;
                }
            } else {
                edges->emplace_back(j,suffix_size);
                break;
            }
        }
    }

    for (auto & e : root_edges) {
        add(text,e,result);
    }
    
    return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
