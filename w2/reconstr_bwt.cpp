// Reconstruct a string from its Burrows–Wheeler transform
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

string reconstruct_bwt(string s, const vector<int>& fl, int n) {
  string ans = "$";
  for (int i = 0; ; i = fl[i]) {
    if (s[i] == '$') break;
    ans += s[i];
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  double start = clock();

  string s; cin >> s;
  int n = s.size();
  vector<pair<char, int>> a(n);
  vector<int> fl(n);
  for (int i = 0; i < n; ++i)
    a[i] = {s[i], i};
  sort(a.begin(), a.end());

  for (int i = 0; i < n; ++i)
    fl[a[i].second] = i;
  cout << reconstruct_bwt(s, fl, n) << endl;

  printf("%.8f\n", (clock() - start) / CLOCKS_PER_SEC);

  return 0;
}
