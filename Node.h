#ifndef NODE_H
#define NODE_H

//Header file for Node.cpp
//Node for a linkedlist, stores a char token which can be read or changed, and a pointer to the next node in the linked list

#include <iostream>

using namespace std;

class Node {
 public:
  Node(char); //constructor
  char getValue(); //returns the value stored in the node
  void setNext(Node*); //sets the pointer to the next node in the linked lists
  Node* getNext(); //gets the pointer to the next node, may be null
 protected:
  char token;
  Node* next;
};
#endif
