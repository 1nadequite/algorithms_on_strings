#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 300005;
const int maxt = 1000000;
int child[maxt][27];
int n, t, T = 0, root = 0;
char c[maxn];
string s;

void add() {
  int x = root, prev, cc;
  for (char c : s) {
    cc = c - 'a' + 1;
    if (child[x][cc] == 0) child[x][cc] = T++;
    prev = x;
    x = abs(child[x][cc]);
  }
  child[prev][cc] *= -1;
}

void rem() {
  int x = root, prev, cc;
  for (char c : s) {
    cc = c - 'a' + 1;
    prev = x;
    x = abs(child[x][cc]);
  }
  child[prev][cc] *= -1;
}

int find(int start) {
  int res = 0;
  int x = root, cc;
  for (int i = start; i < s.size(); ++i) {
    cc = s[i] - 'a' + 1;
    x = child[x][cc];
    if (x < 0) {
        res++;
        x *= -1;
    }
    if (x == 0) break;
  }
  return res;
}

void count() {
  int res = 0, l = 0;
  while (l < s.size()) {
    res += find(l);
    l++;
  }
  printf("%d\n", res);
  fflush(stdout);
}

int main() {
  for (int i = 0; i < maxt; ++i) for (int j = 0; j < 27; ++j) child[i][j] = 0;
  root = T++;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    scanf("%d %s", &t, &c);
    s = c;
    if (t == 1) add();
    else if (t == 2) rem();
    else count();
  }
  
  return 0;
}
