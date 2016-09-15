// Find all occurrences of a pattern in a string.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;
vector<int> res;

vector<int> ComputePrefixFunction(string p) {
  int n = p.size();
  vector<int> s(n);
  s[0] = 0;
  int border = 0;
  for (int i = 1; i < n; ++i) {
    while (border > 0 && p[i] != p[border])
      border = s[border - 1];
    if (p[i] == p[border]) border++;
    else border = 0;
    s[i] = border;
  }
  return s;
}

void FindAllOccurrences(string x, string y) {
  string str = y + '$' + x;
  int ns = str.size(), ny = y.size();
  vector<int> s = ComputePrefixFunction(str);
  for (int i = ny + 1; i < ns; ++i)
    if (s[i] == ny)
      res.push_back(i - 2 * ny);
}

int main() {
  string t, s; cin >> t >> s;
  FindAllOccurrences(s, t);

  for (auto x : res)
    cout << x << ' ';
  cout << endl;

  return 0;
}
