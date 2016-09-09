#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;
const int maxn = 300005;
const int alphabet = 256;
vector<int> p(maxn), c(maxn), cnt(maxn), pn(maxn), cn(maxn);
map<string, int> words;

void add(string s) {
  words[s] = 1;
}

void rem(string s) {
  words[s] = 0;
}

int count(int n, char c, string s) {
  int cnt = 0;
  for (int i = 0; i < n; ++i)
    if (s[i] == c)
      cnt++;
  return cnt;
}

string BWT(string s, int n) {
  for (int i = 0; i < maxn; ++i) {
    p[i] = 0; c[i] = 0; cnt[i] = 0; pn[i] = 0; cn[i] = 0;
  }
  for (int i = 0; i < n; ++i)
    cnt[ s[i] ]++;
  for (int i = 1; i < alphabet; ++i)
    cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; ++i)
    p[ --cnt[ s[i] ] ] = i;
  c[ p[0] ] = 0;
  int classes = 1;
  for (int i = 1; i < n; ++i) {
    if (s[ p[i] ] != s[ p[i - 1] ]) ++classes;
    c[ p[i] ] = classes - 1;
  }

  for (int j = 0; (1 << j) < n; ++j) {
    for (int i = 0; i < n; ++i) {
      pn[i] = p[i] - (1 << j);
      if (pn[i] < 0)
        pn[i] += n;
    }
    for (int i = 0; i < n; ++i) cnt[i] = 0;
    for (int i = 0; i < n; ++i)
      cnt[ c[ pn[i] ] ]++;
    for (int i = 1; i < classes; ++i)
      cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i)
      p[ --cnt[ c[ pn[i] ] ] ] = pn[i];
    cn[p[0]] = 0;
    classes = 1;
    for (int i = 1; i < n; ++i) {
      int mid1 = (p[i] + (1 << j)) % n, mid2 = (p[i - 1] + (1 << j)) % n;
      if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
        ++classes;
      cn[p[i]] = classes - 1;
    }
    for (int i = 0; i < n; ++i)
      c[i] = cn[i];
  }
  string res = "";
  for (int i = 0; i < n; ++i)
    res += s[(p[i] + n - 1) % n];
  return res;
}

int BWMatching(map<char, int>& first_occurence, map<char, int>& last_column, int n, string t, string s) {
  int top = 0, bottom = n - 1;
  while (top <= bottom) {
    if (!t.empty()) {
      char c = *(t.end() - 1);
      t = {t.begin(), t.end() - 1};
      if (last_column[c]) {
        top = first_occurence[c] + count(top, c, s);
        bottom = first_occurence[c] + count(bottom + 1, c, s) - 1;
      } else {
        return 0;
      }
    } else {
      return bottom - top + 1;
    }
  }
  return 0;
}

int find(string s, int n) {
  map<char, int> last_column, first_occurence;
  for (int i = 0; i < n; ++i) {
    if (last_column[s[i]] || s[i] == '$') continue;
    else last_column[s[i]] = 1;
  }
  string ss = s;
  sort(ss.begin(), ss.end());
  for (int i = 0; i < n; ++i) {
    if (first_occurence[ss[i]]) continue;
    else first_occurence[ss[i]] = i;
  }
  int res = 0;
  for (auto x: words)
    if (x.second == 1)
      res += BWMatching(first_occurence, last_column, n, x.first, s);
  return res;
}

int main() {
  int m; cin >> m;
  for (int i = 0; i < m; ++i) {
    int t; string s; cin >> t >> s;
    if (t == 1) add(s);
    else if (t == 2) rem(s);
    else if (t == 3) {
      s += '$';
      cout << find(BWT(s, s.size()), s.size()) << endl;
    }
  }

  return 0;
}
