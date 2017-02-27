//BinaryNode class for creating expression trees
#include <iostream>
#include "Node.h"

using namespace std;

//Constructor: stores a char, sets next to NULL
Node::Node(char newToken){
  token = newToken;
  leftchild = NULL;
  rightchild = NULL;
}

//returns the value stored in the node
char Node::getValue(){
  return token;
}

 //sets the leftchild of this node
void Node::setLeftChild(Node* newNode){
  leftchild = newNode;
}

//sets the rightchild of this node
void Node::setRightChild(Node* newNode){
 rightchild = newNode;
}

//gets the leftchild of the node, may be null
Node* Node::getLeftChild(){
  return leftchild;
}

//gets the rightchild of the node, may be null
Node* Node::getRightChild(){
  return rightchild;
}
