// Construct the Suffix Array of a String
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;
const int maxn = 100005;
vector<int> suffix_array(maxn);
string s;

struct suffix {
  char *suf;
  int index;
};

int cmp(const suffix a, const suffix b) {
  return strcmp(a.suf, b.suf) < 0 ? 1 : 0;
}

void building_suf_array(char* s, int n) {
  vector<suffix> suffixes(n);
  for (int i = 0; i < n; ++i) {
    suffixes[i].index = i;
    suffixes[i].suf = (s + i);
  }
  sort(suffixes.begin(), suffixes.end(), cmp);
  for (int i = 0; i < n; ++i)
    suffix_array[i] = suffixes[i].index;
}

int main() {
  string s; cin >> s;
  int n = s.size();

  building_suf_array(&s[0], n);

  for (int i = 0; i < n; ++i)
    cout << suffix_array[i] << ' ';
  cout << endl;

  return 0;
}
