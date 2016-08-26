// Construct a trie from a collection of patterns
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;
int n, node_num = 0;

struct node {
  vector<node*> a;
  int num_child, node_number;
  node(int n, int num) {
    num_child = n;
    node_number = num;
    for (int i = 0; i < n; ++i)
      a.push_back(NULL);
  }
};
node* root = new node(26, node_num);

void trieConstruction(const string& s) {
  int n = s.size();
  node* cur_node = root;
  for (int w = 0; w < n; ++w) {
    int i = s[w] - 'A';
    if (cur_node->a[i] == NULL) {
      cur_node->a[i] = new node(cur_node->num_child, ++node_num);
      cout << cur_node->node_number << "->" << node_num << ":" << s[w] << endl;
    }
    cur_node = cur_node->a[i];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    trieConstruction(s);
  }

  return 0;
}
