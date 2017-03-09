//Header file for BinaryNode.cpp
//Node for an expression tree, stores int value, Node* leftchild, and Node* rightchild

#include <iostream>

using namespace std;

class BinaryNode {
 public:
  BinaryNode(char); //constructor
  char* getValue(); //returns the char array stored in the node
  char getToken(); //returns the first character stored in the node
  void addToken(char); //adds a token to the end of the char array
  void displayValue(); // displays the entire array backwards to display the numbers correctly
  void setLeftChild(BinaryNode*); //sets the left child of the node
  void setRightChild(BinaryNode*); //sets the right child of the node
  BinaryNode* getLeftChild(); //gets the leftchild of the node, may be null
  BinaryNode* getRightChild(); //gets the rightchild of the node, may be null
 protected:
  char* token;
  BinaryNode* leftchild;
  BinaryNode* rightchild;
};
