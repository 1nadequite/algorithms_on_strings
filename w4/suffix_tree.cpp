// Construct a suffix tree from the suffix array and LCP array of a string.
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 2 * 1e5 + 5;
vector<int> suffix_array(maxn), lcp(maxn);
string s;

struct node {
  node parent;
  map<char, node> children;
  int strDepth;
  int startEdge;
  int endEdge;
};

int main() {
  cin >> s;
  int n = s.size();
  for (int i = 0; i < n; ++i)
    cin >> suffix_array[i];
  for (int i = 0; i < n - 1; ++i)
    cin >> lcp[i];


  return 0;
}
