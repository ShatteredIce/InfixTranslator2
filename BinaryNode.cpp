//BinaryNode class for creating expression trees
#include <iostream>
#include "BinaryNode.h"

using namespace std;

//Constructor: stores a char, sets next to NULL
BinaryNode::BinaryNode(char newToken){
  token = newToken;
  leftchild = NULL;
  rightchild = NULL;
}

//returns the value stored in the node
char BinaryNode::getValue(){
  return token;
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
