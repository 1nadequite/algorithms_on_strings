// Kasai's algorithm for construction of LCP array from Suffix Array
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;
const int maxn = 1e5;
vector<int> suffix_array(maxn), lcp(maxn);
string s;
int n;

void buildLCP() {
  vector<int> pos(n); // inverse of suffix array
  for (int i = 0; i < n; ++i)
    pos[suffix_array[i]] = i;
  int k = 0;
  for (int i = 0; i < n; ++i) {
    if (pos[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = suffix_array[pos[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k])
      k++;
    lcp[pos[i]] = k; // lcp for the present suffix
    if (k > 0)
      k--;
  }
}

int main() {
  cin >> s;
  n = s.size();
  for (int i = 0; i < n; ++i)
    cin >> suffix_array[i];

  buildLCP();

  for (int i = 0; i < n - 1; ++i)
    cout << lcp[i] << ' ';
  cout << endl;

  return 0;
}
