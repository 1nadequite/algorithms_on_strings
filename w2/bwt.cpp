// Construct the Burrows–Wheeler transform of a string
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;
const int maxn = 1005;
const int alphabet = 256;
vector<int> p(maxn), c(maxn), cnt(maxn), pn(maxn), cn(maxn);

void BWT(string s, int n) {
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
}

int main() {
  double start = clock();

  string s; cin >> s;
  int n = s.size();

  BWT(s, n);
  for (int i = 0; i < n; ++i)
    cout << s[(p[i] + n - 1) % n];
  cout << endl;

  printf("%.8f\n", (clock() - start) / CLOCKS_PER_SEC);

  return 0;
}
