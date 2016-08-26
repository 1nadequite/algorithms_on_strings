// Extend TrieMatching algorithm so that it handles correctly cases when one of the patterns is a
// prefix of another one.
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;
set<int> ans;
int n;
string s, t;

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
  return (c - 'A');
}

void trieConstruction() {
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

void prefixTrieMatching(int l, int r) {
  int w = l, i = ch(t[w]);
  node* cur_node = root;
  while (true && w <= r) {
    if (cur_node->is_word) ans.insert(l);
    if (cur_node->a[i] == NULL) return;
    else {
      cur_node = cur_node->a[i];
      i = ch(t[++w]);
    }
  }
}

void trieMatching() {
  int l = 0, r = t.size();
  while (l < r) {
    prefixTrieMatching(l, r);
    l++;
  }
}

int main() {
  cin >> t;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    trieConstruction();
  }
  trieMatching();
  for (auto x: ans)
    cout << x << ' ';
  cout << endl;

  return 0;
}
