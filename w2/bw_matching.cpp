// Implement BetterBWMatching algorithm.
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

int count(int n, char c, string s) {
  int cnt = 0;
  for (int i = 0; i < n; ++i)
    if (s[i] == c)
      cnt++;
  return cnt;
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

int main() {
  double start = clock();

  string s; cin >> s;
  int n = s.size(), m; cin >> m;
  vector<string> str(m);
  for (int i = 0; i < m; ++i)
    cin >> str[i];
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

  for (int i = 0; i < m; ++i)
    cout << BWMatching(first_occurence, last_column, n, str[i], s) << ' ';
  cout << endl;

  printf("%.8f\n", (clock() - start) / CLOCKS_PER_SEC);

  return 0;
}
