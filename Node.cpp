#include "Node.h"

#include <iostream>

using namespace std;

// constructor (no parameter)
Node::Node()
    : count(0),left(nullptr),right(nullptr)
{
}

// constructor (parameter passed in)
Node::Node(const string& s)
    : key(s),count(1),left(nullptr),right(nullptr)
{
}

// tear down left and right subtrees when deleted
Node::~Node() {
  // delete is safe on a nullptr -> no need to check
  delete left;
  delete right;
}

// overload << -> to print key and count
ostream& operator<< ( ostream &os, const Node &a ) {
  os << a.key << "(" << a.count << ")";
  return os;
}

