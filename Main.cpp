//C++ Project 10 - InfixTranslator - 2/27/17
//Creates an expression tree for input in infix notation, then outputs prefix, infix, or postfix notation to the console

#include <iostream>
#include <string.h>
#include "Node.h"
#include "BinaryNode.h"

using namespace std;

//prototypes
Node* peek(Node* head);
Node* pop(Node* & head);
char popValue(Node* & head);
void push(Node* & head, Node* data);
void deleteAllNodes(Node* & head);
void display(Node* current);
void getInput(char* input);
bool isValidInput(char* input);
bool isOperator(char c);
bool isOperator(char* c);
void trimWhitespace(char* input);
int getPrecedence(char c);
void buildTree(BinaryNode* treeNode, Node* outputHead);
void printPostfix(BinaryNode* treeNode);
void printInfix(BinaryNode* treeNode);
void printPrefix(BinaryNode* treeNode);
void deleteTree(BinaryNode*  treeNode);

const int INPUT_SIZE = 201;

int main(){

  Node* inputHead = NULL;
  Node* operatorHead = NULL;
  Node* outputHead = NULL;
  BinaryNode* expTreeHead = NULL;
  Node* temp;
  bool running = true;
  bool easterEgg = false;
  char input[INPUT_SIZE];

  cout << "\n-----Infix Translator v1.0-----\n";
  cout << "Converts expressions into prefix or postfix notation\n";
  cout << "C++ Project 8 - Nathan Purwosumarto\n\n";

  while(running){
    cout << "Infix Notation: ";
    getInput(input);
    //if input = quit, then end the program
    if(strcmp(input, "quit") == 0){
      cout << "\nProgram Terminated." << endl;
      running = false;
    }

    //if the input is only made up of valid characters
    else if(isValidInput(input) && strlen(input) > 0){
      //clear stacks if they are not empty
      if(outputHead != NULL){
        cout << outputHead->getNext()->getValue() <<endl;
        deleteAllNodes(outputHead);
      }
      if(operatorHead != NULL){
        deleteAllNodes(operatorHead);
      }
      inputHead = new Node(input[0]);
      temp = inputHead;
      //build the input queue
      for(int i = 1; i < strlen(input); i++){
        temp->setNext(new Node(input[i]));
        temp = temp->getNext();
      }

      //shunting yard algorithm
      temp = inputHead;
      while(temp != NULL){
        //cout << temp->getValue() << endl;
        //puts value into output stack if it is a digit
        if(isdigit(temp->getValue())){
          push(outputHead, new Node(temp->getValue()));
        }
        //if value is an operator
        else if(isOperator(temp->getValue())){
          if(peek(outputHead)->getValue() != ' '){
            push(outputHead, new Node(' '));
          }
          //while there is an operator token o2 at the top of the operator stack and
          //current operator is left-associative and its precedence is less than or equal to that of o2
          while(peek(operatorHead) != NULL && temp->getValue() != '^' &&
          getPrecedence(temp->getValue()) <= getPrecedence(peek(operatorHead)->getValue())){
            //pop o2 off the operator stack and push onto the output queue
            push(outputHead, pop(operatorHead));
            push(outputHead, new Node(' '));
          }
          //push current operator onto operator stack
          push(operatorHead, new Node(temp->getValue()));
        }
        //if value is left parentheses, push it onto the operator stack
        else if(temp->getValue() == '('){
          push(operatorHead, new Node(temp->getValue()));
        }
        //if value is right parentheses, push it onto the operator stack
        else if(temp->getValue() == ')'){
          while(peek(operatorHead) != NULL && peek(operatorHead)->getValue() != '('){
            push(outputHead, pop(operatorHead));
          }
          //delete the left parentheses
          if(peek(operatorHead) != NULL){
            pop(operatorHead);
          }
          else{
            cout << "<Mismatched Parentheses Detected>\n";
          }
        }
        temp = temp->getNext();
      }
      //while there are no more tokens to read, empty the operator stack
      while(peek(operatorHead) != NULL){
        if(peek(operatorHead)->getValue() == '('){
          cout << "<Mismatched Parentheses Detected>\n";
          pop(operatorHead);
        }
        else{
          push(outputHead, new Node(' '));
          push(outputHead, pop(operatorHead));
        }
      }
      //delete input nodes
      deleteAllNodes(inputHead);
      cout << endl;
      //build the expression tree
      if(outputHead != NULL){
        expTreeHead = new BinaryNode(popValue(outputHead));
      }
      buildTree(expTreeHead, outputHead);
      outputHead = NULL;
      //prompt the user if they want the notation in infix, prefix, or postfix
      cout << "\nDo you wish to print the expression tree? \nCommands: 'prefix', 'infix', 'postfix' or 'next' to continue\n";
      while(!strcmp(input, "next") == 0){
        cout << "Input: ";
        getInput(input);
        //print prefix notation
        if(strcmp(input, "prefix") == 0){
          cout << "\nPrefix Notation: ";
          printPrefix(expTreeHead);
          cout << "\n\n";
        }
        //print infix notation
        else if(strcmp(input, "infix") == 0){
          cout << "\nInfix Notation: ";
          printInfix(expTreeHead);
          if(easterEgg == false){
            cout << "\n";
            cout << "Achievement Unlocked! Infix -> Infix\n\n";
            easterEgg = true;
          }
          else{
            cout << "\n\n";
          }
        }
        //print postfix notation
        else if(strcmp(input, "postfix") == 0){
          cout << "\nPostfix Notation: ";
          printPostfix(expTreeHead);
          cout << "\n\n";
        }
        else if(!strcmp(input, "next") == 0){
          cout << "<Invalid Input>\n";
        }
      }
      cout << endl;
      //delete the tree to avoid memory leak when the head is set to another new BinaryNode
      deleteTree(expTreeHead);
      expTreeHead = NULL;
    }
    else{
      cout << "<Invalid Input>\n\n";
    }
  }
  return 0;
}

//return the last node in the LL
Node* peek(Node* head){
  if(head == NULL){
    return head;
  }
  while(head->getNext() != NULL){
    head = head->getNext();
  }
  return head;
}

//add a node to the end of a LL
void push(Node* & head, Node* data){
  if(head == NULL){
    head = data;
  }
  else{
    peek(head)->setNext(data);
  }
}

//builds the expression tree
void buildTree(BinaryNode* treeNode, Node* outputHead){
  while(outputHead != NULL){
    if(treeNode->getRightChild() != NULL && treeNode->getLeftChild() != NULL){
      break;
    }
    BinaryNode* temp;
    do{
      temp = new BinaryNode(popValue(outputHead));
      //cout << "token: " << temp->getToken() << endl;
    }while(temp->getToken() == ' ');
    //cout << "popped" << temp->getValue() << endl;
    if(treeNode->getRightChild() == NULL){
      //cout << "set right child of " << treeNode->getValue() << " to " << temp->getValue() << endl;
      treeNode->setRightChild(temp);
      if(isOperator(temp->getToken())){
        buildTree(temp, outputHead);
      }
      //if the current node contains a digit, append all following nodes that also contain digits to the treeNode's character array
      else if(isdigit(temp->getToken())){
        while(outputHead != NULL && isdigit(peek(outputHead)->getValue())){
          temp->addToken((popValue(outputHead)));
        }
      }
    }
    else if(treeNode->getLeftChild() == NULL){
      //cout << "set left child of " << treeNode->getValue() << " to " << temp->getValue() << endl;
      treeNode->setLeftChild(temp);
      if(isOperator(temp->getToken())){
        buildTree(temp, outputHead);
      }
      //if the current node contains a digit, append all following nodes that also contain digits to the treeNode's character array
      else if(isdigit(temp->getToken())){
        while(outputHead != NULL && isdigit(peek(outputHead)->getValue())){
          temp->addToken((popValue(outputHead)));
        }
      }
    }
  }
}

//prints an expression tree in postfix notation
void printPostfix(BinaryNode* treeNode){
  if(treeNode->getLeftChild() != NULL){
    printPostfix(treeNode->getLeftChild());
  }
  if(treeNode->getRightChild() != NULL){
    printPostfix(treeNode->getRightChild());
  }
  treeNode->displayValue();
}

//prints an expression tree in infix notation
void printInfix(BinaryNode* treeNode){
  if(treeNode->getLeftChild() != NULL){
    printInfix(treeNode->getLeftChild());
  }
  treeNode->displayValue();
  if(treeNode->getRightChild() != NULL){
    printInfix(treeNode->getRightChild());
  }
}

//prints an expression tree in prefix notation
void printPrefix(BinaryNode* treeNode){
  treeNode->displayValue();
  if(treeNode->getLeftChild() != NULL){
    printPrefix(treeNode->getLeftChild());
  }
  if(treeNode->getRightChild() != NULL){
    printPrefix(treeNode->getRightChild());
  }
}

//removes and returns the last node of a LL
Node* pop(Node* & head){
  Node* temp;
  if(head == NULL){
    return head;
  }
  else if(head->getNext() == NULL){
    temp = new Node(head->getValue());
    delete head;
    head = NULL;
  }
  else{
    Node* current = head;
    //get current equal to second to last node
    while(current->getNext()->getNext() != NULL){
      current = current->getNext();
    }
    temp = new Node(current->getNext()->getValue());
    delete current->getNext();
    current->setNext(NULL);
  }
  return temp;
}

//removes the last node of a LL and returns its value
char popValue(Node* & head){
  char temp;
  if(head == NULL){
    return '\0';
  }
  else if(head->getNext() == NULL){
    temp = head->getValue();
    delete head;
    head = NULL;
  }
  else{
    Node* current = head;
    //get current equal to second to last node
    while(current->getNext()->getNext() != NULL){
      current = current->getNext();
    }
    temp = current->getNext()->getValue();
    delete current->getNext();
    current->setNext(NULL);
  }
  return temp;
}

//deletes all nodes in the LL and sets the head to null
void deleteAllNodes(Node* & head){
  while(head->getNext() != NULL){
    Node* temp = head->getNext();
    delete head;
    head = temp;
  }
  delete head;
  head = NULL;
}

//deletes all nodes in a binary tree and sets the head to null
void deleteTree(BinaryNode*  treeNode){
  if(treeNode->getRightChild() != NULL){
    deleteTree(treeNode->getRightChild());
    treeNode->setRightChild(NULL);
  }
  if(treeNode->getLeftChild() != NULL){
    deleteTree(treeNode->getLeftChild());
    treeNode->setLeftChild(NULL);
  }
  delete treeNode;
  //treeNode = NULL;
}

//displays all nodes in the LL
void display(Node* current){
  if(current != NULL){
    cout << current->getValue();
    display(current = current->getNext());
  }
}

//checks if the user input is valid
bool isValidInput(char* input){
  for(int i = 0; i < strlen(input); i++){
    if(!(isdigit(input[i]) || input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '(' || input[i] == ')' || input[i] == '^' || input[i] == ' ')){
      return false;
    }
  }
  return true;
}

//checks if user input is an operator
bool isOperator(char c){
  if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^'){
    return true;
  }
  return false;
}

//checks if user input is an operator
bool isOperator(char* c){
  if(*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '^'){
    return true;
  }
  return false;
}

//stores user input into a char*
void getInput(char* input){
  fill(input, input + INPUT_SIZE, ' ');
  cin.getline(input, INPUT_SIZE);
  trimWhitespace(input);
}

//remove extra whitespaces to make sure input is compared as intended
void trimWhitespace(char* text){
  char* newText = text;
  char lastChar = ' ';
  while(*text != '\0'){
    if(!(*text == ' ' && lastChar == ' ')){
      *newText = *text;
      lastChar = *text;
      newText++;
    }
    text++;
  }
  if(*(newText-1) != ' '){
    *newText = '\0';
  }
  else{
    *(newText-1) = '\0';
  }
}

//returns operator precedence
int getPrecedence(char c){
  if(c == '+' || c == '-'){
    return 2;
  }
  else if(c == '*' || c == '/'){
    return 3;
  }
  else if(c == '^'){
    return 4;
  }
  else{
    return 0;
  }
}
