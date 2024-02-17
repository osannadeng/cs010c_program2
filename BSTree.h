#pragma once

#include "Node.h"

class BSTree {
  Node* root;

public:
  BSTree()  // constructor
    : root(nullptr)
  {
  }
  ~BSTree() {
    // safe to delete nullptr, so no check needed
    // the Node struct recursively deletes its children
    delete root;
  }
  // rule of three because of destructor
  BSTree(const BSTree&) = delete;
  BSTree& operator=(const BSTree&) = delete;
  
  void insert(const string& key);
  bool search(const string& key) const;
  string largest() const;
  string smallest() const;
  int height(const string& key) const;
  void remove(const string& key);

  void preOrder() const;
  void postOrder() const;
  void inOrder() const;

private:
  // helper functions
  void remove(Node* parent, Node* tree, const string& key);
  int height_of(Node* tree) const;
  void preOrder(Node* tree) const;
  void postOrder(Node* tree) const;
  void inOrder(Node* tree) const;
};
