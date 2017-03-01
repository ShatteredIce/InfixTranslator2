//Header file for BinaryNode.cpp
//Node for an expression tree, stores int value, Node* leftchild, and Node* rightchild

#include <iostream>

using namespace std;

class BinaryNode {
 public:
  BinaryNode(char); //constructor
  char getValue(); //returns the value stored in the node
  void setLeftChild(BinaryNode*); //sets the left child of the node
  void setRightChild(BinaryNode*); //sets the right child of the node
  BinaryNode* getLeftChild(); //gets the leftchild of the node, may be null
  BinaryNode* getRightChild(); //gets the rightchild of the node, may be null
 protected:
  char token;
  BinaryNode* leftchild;
  BinaryNode* rightchild;
};
