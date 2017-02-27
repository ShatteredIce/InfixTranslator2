//Header file for BinaryNode.cpp
//Node for an expression tree, stores int value, Node* leftchild, and Node* rightchild

#include <iostream>

using namespace std;

class Node {
 public:
  Node(char); //constructor
  char getValue(); //returns the value stored in the node
  void setLeftChild(Node*); //sets the left child of the node
  void setRightChild(Node*); //sets the right child of the node
  Node* getLeftChild(); //gets the leftchild of the node, may be null
  Node* getRightChild(); //gets the rightchild of the node, may be null
 protected:
  char token;
  Node* leftchild;
  Node* rightchild;
};
