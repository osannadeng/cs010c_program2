#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// adds key into tree
// increases count if already in tree
// else makes new node to add into a hole in tree
void BSTree::insert(const string& key) {
  // node is empty
  if (root == nullptr) {
    root = new Node(key);
    return;
  }
  Node* curr = root;
  while (curr) {
    // already in tree
    if (key == curr->key) {
      ++curr->count;
      return;
    }
    // move to left branch
    if (key < curr->key) {
      if (curr->left == nullptr) {  // found hole (no child)
        curr->left = new Node(key);
        return;
      }
      curr = curr->left;
    } else {  // move to right branch
      if (curr->right == nullptr) { // found hole (no child)
        curr->right = new Node(key);
        return;
      }
      curr = curr->right;
    }
  }
}

// determine if key is in tree
// true if so, false otherwise
bool BSTree::search(const string& key) const {
  Node* curr = root;
  while (curr) {  // run through tree to where key should be
    if (key == curr->key) return true;
    if (key < curr->key) curr = curr->left;
    else if (key > curr->key) curr = curr->right;
  }
  return false; // key never matches
}

// returns largest (right-most) key in tree
string BSTree::largest() const {
  // tree is empty, would normally throw error
  if (root == nullptr) return "";
  Node* curr = root;
  // iterate through until right-most is reached
  while (curr->right) {
    curr = curr->right;
  }
  return curr->key;
}

// returns smallest (left-most) key in the tree
string BSTree::smallest() const {
  // tree is empty, would normally throw error
  if (root == nullptr) return "";
  Node* curr = root;
  // iterate through until left-most is reached
  while (curr->left) {
    curr = curr->left;
  }
  return curr->key;
}

// returns height of tree starting at key
// (as if root was key)
int BSTree::height(const string& key) const {
  Node* curr = root;
  while (curr) {  // find node with key
    if (key == curr->key) break;
    if (key < curr->key) curr = curr->left;
    else if (key > curr->key) curr = curr->right;
  }
  // if using throws, would throw error if key is not in tree
  return height_of(curr); // call helper function
}

// removes one of the key
// if multiple, count is decreased
// else removes node according to spot in tree
void BSTree::remove(const string& key) {
  remove(nullptr, root, key); // calls helper function
}

// prints list in pre-order format
// with ", " after every node and newline when done
void BSTree::preOrder() const {
  preOrder(root); // call helper
  cout << endl;
}

// prints list in post-order format
// with ", " after every node and newline when done
void BSTree::postOrder() const {
  postOrder(root);  // call helper
  cout << endl;
}

// prints list in order
// with ", " after every node and newline when done
void BSTree::inOrder() const {
  inOrder(root); // call helper
  cout << endl;
}

// remove helper function, recursive, overloads public remove
// private, uses additional parameters that shouldn't be accessed publically for this
void BSTree::remove(Node* parent, Node* tree, const string& key) {
  if (tree == nullptr) return;  // key is not found, would normally throw error
  if (key == tree->key) { // key is found
    --tree->count;
    // to remove node from tree if it was the only copy of key, else only decrements
    if (tree->count == 0) {
      // leaf
      if (tree->left == nullptr && tree->right == nullptr) {
        // key is at root
        if (parent == nullptr) {
          delete tree;
          root = nullptr;
          return;
        }
        // tree is left child
        if (tree == parent->left) {
          delete tree;
          parent->left = nullptr;
        } else {  // is right child
          delete tree;
          parent->right = nullptr;
        }
        return;
      }
      // has left or both subtree(s)
      if (tree->left) {
        // find largest of left tree
        Node* largest = tree->left;
        while (largest->right) {
          largest = largest->right;
        }
        // copy information
        tree->key = largest->key;
        tree->count = largest->count;
        // delete copied node, recursive
        largest->count = 1;
        remove(tree, tree->left, tree->key);
        return;
      }
      // right subtree
      if (tree->right) {
        // find smallest of right tree
        Node* smallest = tree->right;
        while (smallest->left) {
          smallest = smallest->left;
        }
        // copy information
        tree->key = smallest->key;
        tree->count = smallest->count;
        // delete copied node, recursive
        smallest->count = 1;
        remove(tree, tree->right, tree->key);
        return;
      }
    }
  } else {  // key not found yet, recursive
    parent = tree;
    if (key < tree->key) tree = tree->left;
    else tree = tree->right;
    remove(parent, tree, key);
  }
}

// height helper function, recursive
// private, find height starting at given node
// returns largest height from left and right subtrees + 1
int BSTree::height_of(Node* tree) const {
  // bottom or not found
  // if only root then both sides are -1, results in height of 0
  if (tree == nullptr) return -1;
  int countLeft = height_of(tree->left);
  int countRight = height_of(tree->right);
  if (countLeft > countRight) return countLeft + 1;
  return countRight + 1;
}

// preOrder helper, recursive, overloads public
// private, uses extra parameter that should not be accessed for this publically
void BSTree::preOrder(Node* tree) const {
  // print key, do left, do right
  if (tree == nullptr) return;
  cout << *tree << ", ";
  preOrder(tree->left);
  preOrder(tree->right);
}

// postOrder helper, recursive, overloads public
// private, uses extra parameter that should not be accessed for this publically
void BSTree::postOrder(Node* tree) const {
  // do left, do right, print key
  if (tree == nullptr) return;
  postOrder(tree->left);
  postOrder(tree->right);
  cout << *tree << ", ";
}

// inOrder helper, recursive, overloads public
// private, uses extra parameter that should not be accessed for this publically
void BSTree::inOrder(Node* tree) const {
  // do left, print key, do right
  if (tree == nullptr) return;
  inOrder(tree->left);
  cout << *tree << ", ";
  inOrder(tree->right);
}