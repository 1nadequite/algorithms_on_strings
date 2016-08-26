// Construct the suffix tree of a string.
#include <iostream>
#include <vector>
#include <string>

using namespace std;
string s;

struct node {
  vector<node*> a;
  int left;
  int right;
  bool is_word;
  node() {
    is_word = false;
    for (int i = 0; i < 26; ++i)
      a.push_back(NULL);
  }
};
node* root = new node();

int cr(char c) {
  return (c - 'A');
}

void initTree() {
  root->is_word = true;
}

void insertTree(int l, int r, node* cur_node) {
  if (s[l] == '$') return;
  int i = cr(s[l]);
  if (cur_node->a[i] == NULL) {
    cur_node->a[i] = new node();
    cur_node->a[i]->left = l;
    cur_node->a[i]->right = r;
    cur_node->a[i]->is_word = true;
    return;
  }
  cur_node = cur_node->a[i];
  int w = l, tmp_left = cur_node->left;
  int j = cr(s[tmp_left]);

  while (w < r && tmp_left < cur_node->right) {
    if (i != j) break;
    i = cr(s[++w]);
    j = cr(s[++tmp_left]);
  }
  cur_node->right = tmp_left;
  if (s[w] == '$' || s[tmp_left] == '$') cur_node->is_word = true;
  else cur_node->is_word = false;

  insertTree(w, r, cur_node);
  insertTree(tmp_left, r, cur_node);

  return;
}

void suffixTree() {
  int r = s.size() - 1, l = r - 1;
  while (l >= 0) {
    insertTree(l, r, root);
    l--;
  }
}

void printTree(string& str, node* cur_node) {
  if (cur_node->is_word) cout << str << '$' << endl;
  else cout << str << endl;
  for (int i = 0; i < 26; ++i) {
    if (cur_node->a[i] != NULL) {
      string str = {s.begin() + cur_node->a[i]->left, s.begin() + cur_node->a[i]->right};
      printTree(str, cur_node->a[i]);
    }
  }
  return;
}

int main() {
  cin >> s;
  initTree();
  suffixTree();
  string t = "";
  printTree(t, root);

  return 0;
}
