#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct node {
  vector<node*> child;
  int num_of_child;
  bool is_word;

  node(int n) {
    num_of_child = n;
    is_word = false;
    for (int i = 0; i < n; ++i)
      child.push_back(NULL);
  }
};

class Trie {
public:
  Trie(int n = 26) {root = new node(n);}
  int CharToInt(char);
  void TrieConstruction(const string&);
  void RemoveNode(const string&);
  int PrefixTrieMatching(const string&, node*);
  int TrieMatching(string&, node*);
  node* GetRoot() {return root;}
private:
  node* root;
};

int Trie::CharToInt(char c) {
  return (c - 'a');
}

void Trie::TrieConstruction(const string& s) {
  node* cur_node = root;
  int n = s.size();
  for (int w = 0; w < n; ++w) {
    int i = CharToInt(s[w]);
    if (cur_node->child[i] == NULL)
      cur_node->child[i] = new node(cur_node->num_of_child);
    cur_node = cur_node->child[i];
  }
  if (!cur_node->is_word)
    cur_node->is_word = true;
}

void Trie::RemoveNode(const string& s) {
  node* cur_node = root;
  int n = s.size();
  for (int w = 0; w < n; ++w) {
    int i = CharToInt(s[w]);
    cur_node = cur_node->child[i];
  }
  cur_node->is_word = false;
}

int Trie::PrefixTrieMatching(const string& s, node* root) {
  //cout << s.size() << ' ' << s << endl;
  int j = 0, i = CharToInt(s[j]);
  node* cur_node = root;
  int cur_word = 0;
  while (true) {
    //cout << cur_word << endl;
    j++;
    if (cur_node->is_word) {
      cur_word++;
    }
    if (cur_node->child[i] == NULL) {
      return cur_word;
    } else {
      cur_node = cur_node->child[i];
      i = CharToInt(s[j]);
    }
  }
  return cur_word;
}

int Trie::TrieMatching(string& s, node* root) {
  int words = 0;
  while (!s.empty()) {
    words += PrefixTrieMatching(s, root);
    s = {s.begin() + 1, s.end()};
  }
  return words;
}

int main() {
  int n; cin >> n;
  Trie a(26);
  for (int i = 0; i < n; ++i) {
    int t; string s; cin >> t >> s;
    if (t == 1) a.TrieConstruction(s);
    else if (t == 2) a.RemoveNode(s);
    else if (t == 3) cout << a.TrieMatching(s, a.GetRoot()) << endl;
  }

  return 0;
}
