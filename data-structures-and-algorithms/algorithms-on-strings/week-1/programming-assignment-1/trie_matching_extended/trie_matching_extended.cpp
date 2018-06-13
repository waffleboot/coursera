#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
    vector <int> result;
    
    vector <Node> nodes (1);
    
    for (auto & pattern : patterns) {
        size_t pos = 0;
        for (auto ch : pattern) {
            auto & v = nodes[pos];
            auto idx = letterToIndex(ch);
            auto nxt = v.next[idx];
            if (nxt != NA) {
                pos = nxt;
            } else {
                v.next[idx] = pos = nodes.size();
                nodes.push_back(Node());
            }
        }
        nodes[pos].patternEnd = true;
    }
    
    for (size_t i = 0; i < text.size(); ++i) {
        size_t pos = 0;
        for (size_t j = i; j < text.size(); ++j) {
            auto & v = nodes[pos];
            auto next = v.next[letterToIndex(text[j])];
            if (next == NA) break;
            if (nodes[next].patternEnd) {
                result.push_back(i);
                break;
            }
            pos = next;
        }
    }
    
    return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
