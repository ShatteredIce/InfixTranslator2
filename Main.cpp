//C++ Project 10 - InfixTranslator - 2/27/17
//Creates an expression tree for input in infix notation, then outpus prefix, infix, or postfix notation to the console

#include <iostream>
#include <string.h>
#include "Node.h"

using namespace std;

//prototypes
Node* peek(Node* head);
Node* pop(Node* & head);
void push(Node* & head, Node* data);
void deleteAllNodes(Node* & head);
void display(Node* current);
void getInput(char* input);
bool isValidInput(char* input);
bool isOperator(char c);
void deleteWhitespace(char* input);
int getPrecedence(char c);

int main(){

  Node* inputHead = NULL;
  Node* operatorHead = NULL;
  Node* outputHead = NULL;
  Node* temp;
  bool running = true;
  char input[81];

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
        //puts value into output stack if it is a digit
        if(isdigit(temp->getValue())){
          push(outputHead, new Node(temp->getValue()));
        }
        //if value is an operator
        else if(isOperator(temp->getValue())){
          //while there is an operator token o2 at the top of the operator stack and
          //current operator is left-associative and its precedence is less than or equal to that of o2
          while(peek(operatorHead) != NULL && temp->getValue() != '^' &&
          getPrecedence(temp->getValue()) <= getPrecedence(peek(operatorHead)->getValue())){
            //pop o2 off the operator stack and push onto the output queue
            push(outputHead, pop(operatorHead));
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
          push(outputHead, pop(operatorHead));
        }
      }
      //delete input nodes
      deleteAllNodes(inputHead);
      //print out result
      cout << "Postfix Notation: ";
      display(outputHead);
      cout << endl << endl;
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
    if(!(isdigit(input[i]) || input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '(' || input[i] == ')' || input[i] == '^')){
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

//stores user input into a char*
void getInput(char* input){
  fill(input, input + 81, ' ');
  cin.getline(input, 81);
  deleteWhitespace(input);
}

//deletes all whitespace from a char*
void deleteWhitespace(char* text){
  char* newText = text;
  while(*text != '\0'){
    if(!(*text == ' ')){
      *newText = *text;
      newText++;
    }
    text++;
  }
  *newText = '\0';
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
