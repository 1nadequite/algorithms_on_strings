// Construct a suffix tree from the suffix array and LCP array of a string.
// time: O(n)
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 2 * 1e5 + 5;
vector<int> suffix_array(maxn), lcp(maxn);
string s;
int n;

struct node {
  node* parent;
  map<char, node*> children;
  int strDepth;
  int edgeStart;
  int edgeEnd;
  node() {
    parent = NULL;
    strDepth = 0;
    edgeStart = -1;
    edgeEnd = -1;
  }
};

node* createNewLeaf(node* curNode, int suffix) {
  node* leaf = new node();
  leaf->parent = curNode;
  leaf->strDepth = n - suffix;
  leaf->edgeStart = curNode->strDepth + suffix;
  leaf->edgeEnd = n;
  curNode->children[s[leaf->edgeStart]] = leaf;
  return leaf;
}

node* breakEdge(node* curNode, int start, int offset) {
  char startChar = s[start];
  char midChar = s[start + offset];
  node* midNode = new node();
  midNode->parent = curNode;
  midNode->strDepth = curNode->strDepth + offset;
  midNode->edgeStart = start;
  midNode->edgeEnd = start + offset;

  midNode->children[midChar] = curNode->children[startChar];
  //curNode->children[startChar] = midNode;
  curNode->children[startChar]->parent = midNode;
  curNode->children[startChar]->edgeStart += offset;
  curNode->children[startChar] = midNode;
  return midNode;
}

void STfromSA(node* root) {
  int lcpPrev = 0;
  node* curNode = root;
  for (int i = 0; i < n; ++i) {
    int suffix = suffix_array[i];
    while (curNode->strDepth > lcpPrev)
      curNode = curNode->parent;
    if (curNode->strDepth == lcpPrev) {
      curNode = createNewLeaf(curNode, suffix);
    } else {
      int edgeStart = suffix_array[i - 1] + curNode->strDepth;
      int offset = lcpPrev - curNode->strDepth;
      node* midNode = breakEdge(curNode, edgeStart, offset);
      curNode = createNewLeaf(midNode, suffix);
    }
    if (i < n - 1)
      lcpPrev = lcp[i];
  }
}

void printSuffixTree(node* root) {
  node* curNode = root;
  if (curNode->parent != NULL) {
    string t = {s.begin() + curNode->edgeStart, s.begin() + curNode->edgeEnd};
    cout << curNode->edgeStart << ' ' << curNode->edgeEnd << ' ' << t << endl;
  }
  for (auto child: curNode->children)
    printSuffixTree(child.second);
}

int main() {
  cin >> s;
  n = s.size();
  for (int i = 0; i < n; ++i)
    cin >> suffix_array[i];
  for (int i = 0; i < n - 1; ++i)
    cin >> lcp[i];

  node* root = new node();

  STfromSA(root);

  cout << s << endl;
  printSuffixTree(root);

  return 0;
}
