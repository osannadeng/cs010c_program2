#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Node {
  // as a struct, all these members are public (which is fine)
  string key;
  int count;
  Node *left;
  Node *right;

  Node();
  Node(const string& s);

  // rule of three since I have a destructor that tears down the entire
  // tree starting here (treating this node as a mini-root value)
  ~Node();
  Node(const Node& other) = delete;
  Node& operator=(const Node &rhs) = delete;
};

// If I have a Node* n, I want to be able to do 'cout << *n << endl;'
std::ostream& operator<< ( std::ostream &os, const Node &a );

