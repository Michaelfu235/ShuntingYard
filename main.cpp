//Author: Michael Fu
//Date: 2/27/2024
//Description:

#include <iostream>
#include <cstring>

using namespace std;


class Node {

public:
  
  char data;
  Node* next;
  Node* left;
  Node* right;

  Node(char value){
    data = value;
    next = NULL;
    left = NULL;
    right = NULL;
  }
  /*
  char getData(){
    return data;
    
  }
  Node* getnext(){
    return next;
  }
  void setNext(Node* node){
    ext = node;
  }
  Node* getLeft() {
    return left;
  }
  
  void setLeft(Node* node) {
    left = node;
  }
  
  Node* getRight() {
    return right;
  }
  
  void setRight(Node* node) {
    right = node;
    }*/
};

Node* queueHead = NULL;
Node* stackHead = NULL;

void enqueue(Node* &current, char data);
void dequeue(Node* &head);
void push(Node* &current, char data);
Node* peek(Node* current);
void pop(Node* &current);
void printQS(Node* current);
int precede(char op);
bool isOpp(char op);


int main(){
  int idekatthispoint = 0;
  char inputt[30];

  cout << "input a infex expression with only numbers and '+', '-', '*', '/', '^', '(', ')' " << endl;
  cout << "put space between the numbers and expressions" << endl;

  cin.get(inputt, 30, '\n');
  cin.ignore();

  for(int i = 0;i<strlen(inputt);i++){
    if(!isspace(inputt[i])){
	if(isdigit(inputt[i])){
	  enqueue(queueHead, inputt[i]);
	} else if(inputt[i]==')'){
	  while(peek(stackHead)->data != '('){
	    enqueue(queueHead, peek(stackHead)->data);
	    pop(stackHead);
	  }
	  if(peek(stackHead)->data == '('){
	    pop(stackHead);
	  }
	} else if(!isdigit(inputt[i]) && inputt[i] != '('){
	  while(peek(stackHead) != NULL && isOpp(peek(stackHead)->data) && precede(inputt[i]) <= precede(peek(stackHead)->data)){
	    enqueue(queueHead, peek(stackHead)->data);
	    pop(stackHead);
	  }
	  push(stackHead, inputt[i]);
	}
	
      }
  }
  while(stackHead != NULL){
    enqueue(queueHead, peek(stackHead)->data);
    pop(stackHead);
  }

  cout << "postfix:" << endl;
  printQS(queueHead);
  /*
  enqueue(queueHead, '1');
  enqueue(queueHead, '+');
  enqueue(queueHead, '2');
  enqueue(queueHead, '-');
  enqueue(queueHead, '3');
  enqueue(queueHead, '*');
  enqueue(queueHead, '4');
  enqueue(queueHead, '/');
  enqueue(queueHead, '5');
  printQS(queueHead);
  dequeue(queueHead);
  dequeue(queueHead);
  printQS(queueHead);
  push(stackHead, '1');
  push(stackHead, '+');
  push(stackHead, '2');
  push(stackHead, '-');
  push(stackHead, '3');
  push(stackHead, '*');
  push(stackHead, '4');
  push(stackHead, '/');
  push(stackHead, '5');
  printQS(stackHead);
  cout << peek(stackHead)->data << endl;
  pop(stackHead);
  pop(stackHead);
  cout << peek(stackHead)->data << endl;
  printQS(stackHead);*/

}

void enqueue(Node* &current, char data){
  Node* newNode = new Node(data);
  //newNode->next = NULL;
  if(queueHead == NULL){
    
    queueHead = newNode;
  } else {
    Node* temp = current;
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = newNode;
  }
  
}

void dequeue(Node* &head){
  if(head == NULL){
    return;
  }
  if(head->next==NULL){
    delete head;
    head = NULL;
    queueHead = NULL;
  } else {
    Node* temp = head->next;
    head = temp;
    queueHead = temp;
  }
}

void push(Node* &current, char data){
  Node* newNode = new Node(data);
  if(current == NULL){
    current = newNode;
    stackHead = newNode;
    
  } else {
    Node* temp = current;
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = newNode;
  }
}


Node* peek(Node* current){
  if(current == NULL){
    return NULL;
  } else {
    while(current->next != NULL){
      current = current->next;
    }
    return current;
  }
}

void pop(Node* &current){
  
  if(stackHead->next == NULL){    
    stackHead = NULL;
  } else {
    Node* temp = stackHead;
    while(temp->next->next != NULL){
      temp = temp->next;
    }
    temp->next = NULL;
  }
}



void printQS(Node* current){
  //just for debugging, wont be used in algorithm itself, its just a basic recursive print linked list (wether queue or stack) that prints the next node over and over
  
  if(current != NULL){
    cout << current->data << " -> ";
    printQS(current->next);
  } else {
    cout << "end" << endl;
  }
}


int precede(char op){
  if(op == '^'){
    return 3;
  } else if (op == '*' || op == '/'){
    return 2;
    
  } else if (op == '+' || op == '-'){
    return 1;
  }
  return 0;
}


bool isOpp(char op){
  if(op == '^' || op == '*' || op == '/' || op == '+' || op == '-') {
    return true;
  } else {
    return false;
  }
}
