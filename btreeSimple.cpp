#include <iostream>
using namespace std;

class TreeNode {
  int *keys;
  int t;
  TreeNode **C;
  int n;
  bool leaf;

public:
  TreeNode(int temp, bool bool_leaf);

  void insertNonFull(int k);
  void splitChild(int i, TreeNode *y);
  void printTree(int level);

  friend class BTree;
};

class BTree {
  TreeNode *root;
  int t;

public:
  BTree(int temp) {
    root = NULL;
    t = temp;
  }

  void printTree() {
    if (root != NULL)
      root->printTree(0);
  }

  void insert(int k);
};

TreeNode::TreeNode(int t1, bool leaf1) {
  t = t1;
  leaf = leaf1;

  keys = new int[2 * t - 1];
  C = new TreeNode *[2 * t];

  n = 0;
}

void TreeNode::printTree(int level) {
  cout << "Level " << level << ": ";
  for (int i = 0; i < n; i++)
    cout << keys[i] << " ";
  cout << endl;

  if (!leaf) {
    for (int i = 0; i <= n; i++) {
      C[i]->printTree(level + 1);
    }
  }
}

void BTree::insert(int k) {
  if (root == NULL) {
    root = new TreeNode(t, true);
    root->keys[0] = k;
    root->n = 1;
  } else {
    if (root->n == 2 * t - 1) {
      TreeNode *s = new TreeNode(t, false);

      s->C[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertNonFull(k);

      root = s;
    } else
      root->insertNonFull(k);
  }
}

void TreeNode::insertNonFull(int k) {
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k)
      i--;

    if (C[i + 1]->n == 2 * t - 1) {
      splitChild(i + 1, C[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    C[i + 1]->insertNonFull(k);
  }
}

void TreeNode::splitChild(int i, TreeNode *y) {
  TreeNode *z = new TreeNode(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++)
    z->keys[j] = y->keys[j + t];

  if (y->leaf == false) {
    for (int j = 0; j < t; j++)
      z->C[j] = y->C[j + t];
  }

  y->n = t - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[t - 1];
  n = n + 1;
}

int main() {
  int degree;
  cout << "Enter the minimum degree of the B-tree: ";
  cin >> degree;

  BTree t(degree);

  int choice, key;
  while (true) {
    cout << "\n1. Insert key\n2. Print tree\n3. Exit\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
      case 1:
        cout << "Enter key to insert: ";
        cin >> key;
        t.insert(key);
        break;
      case 2:
        cout << "The B-tree structure is:\n";
        t.printTree();
        break;
      case 3:
        cout << "Exiting...\n";
        return 0;
      default:
        cout << "Invalid choice! Try again.\n";
    }
  }
}
