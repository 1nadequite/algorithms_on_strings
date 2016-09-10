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
string s, pat;

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

void search(char* pat, char* s, int n, int m) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int mid = l + (r - l) / 2;
    int res = strncmp(pat, s + suffix_array[mid], m);
    if (res == 0) {
      cout << suffix_array[mid] << endl;
      return;
    }
    if (res < 0) r = mid - 1;
    else l = mid + 1;
  }
  cout << "Pattern not found" << endl;
}

int main() {
  cin >> s >> pat;
  int n = s.size(), m = pat.size();

  building_suf_array(&s[0], n);

  search(&pat[0], &s[0], n, m);

  return 0;
}
