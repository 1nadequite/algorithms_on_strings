#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 300005;
int n, t;
char c[maxn];
string s;

struct node {
  vector<node*> a;
  int num_child;
  bool is_word;
  node(int n) {
    num_child = n;
    is_word = false;
    for (int i = 0; i < n; ++i)
      a.push_back(NULL);
  }
};
node* root = new node(26);

int ch(char c) {
  return (c - 'a');
}

void add() {
  int n = s.size();
  node* cur_node = root;
  for (int w = 0; w < n; ++w) {
    int i = ch(s[w]);
    if (cur_node->a[i] == NULL) {
      cur_node->a[i] = new node(cur_node->num_child);
    }
    cur_node = cur_node->a[i];
  }
  if (!cur_node->is_word) {
    cur_node->is_word = true;
  }
}

void rem() {
  int n = s.size();
  node* cur_node = root;
  for (int w = 0; w < n; ++w) {
    int i = ch(s[w]);
    cur_node = cur_node->a[i];
  }
  cur_node->is_word = false;
}

int find(int l, int r) {
  int w = l, i = ch(s[w]);
  node* cur_node = root;
  int res = 0;
  while (true && w <= r) {
    if (cur_node->is_word) res++;
    if (cur_node->a[i] == NULL) return res;
    else {
      cur_node = cur_node->a[i];
      i = ch(s[++w]);
    }
  }
  return res;
}

void count() {
  int res = 0, l = 0, r = s.size();
  while (l < r) {
    res += find(l, r);
    l++;
  }
  printf("%d\n", res);
  fflush(stdout);
}

int main() {
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
