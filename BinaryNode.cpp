//BinaryNode class for creating expression trees
#include <iostream>
#include "BinaryNode.h"

using namespace std;

//Constructor: stores a char, sets next to NULL
BinaryNode::BinaryNode(char newToken){
  token = new char[81];
  token[0] = newToken;
  leftchild = NULL;
  rightchild = NULL;
}

//returns the char array stored in the node
char* BinaryNode::getValue(){
  return token;
}

char BinaryNode::getToken(){
  return token[0];
}
 //sets the leftchild of this node
void BinaryNode::setLeftChild(BinaryNode* newNode){
  leftchild = newNode;
}

//sets the rightchild of this node
void BinaryNode::setRightChild(BinaryNode* newNode){
 rightchild = newNode;
}

//gets the leftchild of the node, may be null
BinaryNode* BinaryNode::getLeftChild(){
  return leftchild;
}

//gets the rightchild of the node, may be null
BinaryNode* BinaryNode::getRightChild(){
  return rightchild;
}
