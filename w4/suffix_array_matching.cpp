// Find all occurrences of a given collection of patterns in a string.
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 2 * 1e5 + 5;
const int alphabet = 256;
vector<int> order(maxn), classes(maxn);
set<int> occurrences;
string s, pat;
int n, m;

vector<int> sortCharacters() {
  vector<int> order(maxn), cnt(alphabet);
  for (int i = 0; i < n; ++i)
    cnt[s[i]]++;
  for (int i = 1; i < alphabet; ++i)
    cnt[i] += cnt[i - 1];
  for (int i = n - 1; i >= 0; --i) {
    int c = s[i];
    cnt[c]--;
    order[cnt[c]]= i;
  }
  return order;
}

vector<int> computeCharClasses(const vector<int>& order) {
  vector<int> classes(maxn);
  classes[order[0]] = 0;
  for (int i = 1; i < n; ++i) {
    if (s[order[i]] != s[order[i - 1]])
      classes[order[i]] = classes[order[i - 1]] + 1;
    else
      classes[order[i]] = classes[order[i - 1]];
  }
  return classes;
}

vector<int> sortDoubled(int l, const vector<int>& order, const vector<int>& classes) {
  vector<int> cnt(n), newOrder(maxn);
  for (int i = 0; i < n; ++i)
    cnt[classes[i]]++;
  for (int i = 1; i < n; ++i)
    cnt[i] += cnt[i - 1];
  for (int i = n - 1; i >= 0; --i) {
    int start = (order[i] - l + n) % n;
    int c = classes[start];
    cnt[c]--;
    newOrder[cnt[c]] = start;
  }
  return newOrder;
}

vector<int> updateClasses(int l, const vector<int>& newOrder, const vector<int>& classes) {
  vector<int> newClasses(maxn);
  newClasses[newOrder[0]] = 0;
  for (int i = 1; i < n; ++i) {
    int cur = newOrder[i];
    int prev = newOrder[i - 1];
    int mid = (cur + l) % n;
    int midPrev = (prev + l) % n;
    if (classes[cur] != classes[prev] || classes[mid] != classes[midPrev])
      newClasses[cur] = newClasses[prev] + 1;
    else
      newClasses[cur] = newClasses[prev];
  }
  return newClasses;
}

vector<int> buildSuffixArray() {
  order = sortCharacters();
  classes = computeCharClasses(order);
  int l = 1;
  while (l < n) {
    order = sortDoubled(l, order, classes);
    classes = updateClasses(l, order, classes);
    l *= 2;
  }
  return order;
}

void search(char* s, char* pat, const vector<int>& suffix_array, int m) {
  for (int i = 0; i < n; ++i) {
    int res = strncmp(pat, s + suffix_array[i], m);
    if (res == 0) occurrences.insert(suffix_array[i]);
  }
}

int main() {
  cin >> s >> m;
  s += '$';
  n = s.size();

  vector<int> suffix_array = buildSuffixArray();

  for (int i = 0; i < m; ++i) {
    cin >> pat;
    search(&s[0], &pat[0], suffix_array, pat.size());
  }

  for (auto x: occurrences)
    cout << x << ' ';
  cout << endl;

  return 0;
}
