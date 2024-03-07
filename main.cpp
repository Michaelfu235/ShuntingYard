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
void push(Node* &current, char data, Node* datt);
Node* peek(Node* current);
void pop(Node* &current);
void printQS(Node* current);
int precede(char op);
bool isOpp(char op);
void buildTree(Node* current);
void infix(Node* current);
void prefix(Node* current);
void postfix(Node* current);


int main(){
  bool justKeepGoing = true;
  while(justKeepGoing){

    queueHead = NULL;
    stackHead = NULL;
    int idekatthispoint = 0;
    char inputt[30];

    cout << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "input a infex expression with only numbers and '+', '-', '*', '/', '^', '(', ')' " << endl;
    cout << "put space between the numbers and expressions" << endl;

    cin.get(inputt, 30, '\n');
    cin.ignore();

    for(int i = 0;i<strlen(inputt);i++){
      if(!isspace(inputt[i])){
	if(isdigit(inputt[i])){
	  enqueue(queueHead, inputt[i]);
	} else if(inputt[i] == '('){
	  push(stackHead, inputt[i], NULL);
	
	} else if(inputt[i]==')'){
	  while(peek(stackHead)->data != '('){
	    enqueue(queueHead, peek(stackHead)->data);
	    pop(stackHead);
	    //with the ^ commented out, the program runs forever, but with it in it gets a segmentation fault when using parenthesis
	    //nvm I fixed it
	  }
	  
	  if(peek(stackHead)->data == '('){
	    pop(stackHead);
	  }
	} else if(inputt[i] != '(' && !isdigit(inputt[i])){
	  while(peek(stackHead) != NULL && isOpp(peek(stackHead)->data) && precede(inputt[i]) <= precede(peek(stackHead)->data)){
	    enqueue(queueHead, peek(stackHead)->data);
	    pop(stackHead);
	  }
	  
	  push(stackHead, inputt[i], NULL);
	}
	
      }
    }
    while(stackHead != NULL){
      enqueue(queueHead, peek(stackHead)->data);
      pop(stackHead);
    }

    while(queueHead != NULL){
      buildTree(queueHead);
      dequeue(queueHead);
    }

    bool justKeepGoing2 = true;
    while(justKeepGoing2 == true){
      cout << endl;
      cout << "do you want it in prefix(E), infix(I) or postfix(O), or new expression(N) or quit(Q)" << endl;
      char inputy;
      cin >> inputy;
      cin.ignore();
      if(inputy == 'E'){
	prefix(stackHead);
      } else if (inputy == 'I'){
	infix(stackHead);
      } else if (inputy == 'O'){
	postfix(stackHead);
      } else if (inputy == 'N'){
	justKeepGoing2 = false;
      } else if (inputy == 'Q'){
	justKeepGoing2 = false;
	justKeepGoing = false;
      }
    }

    /*
    
    cout << "postfix:" << endl;
    printQS(queueHead);
    cout << " " << endl;
    printQS(stackHead);


  
    //turning the postfix into a tree
    while(queueHead != NULL){
      buildTree(queueHead);
      dequeue(queueHead);
    }

    infix(stackHead);
    cout << endl;
    cout << "--------------" << endl;
    postfix(stackHead);
    cout << endl;
    cout << "-------------" << endl;
    prefix(stackHead);
  
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

void push(Node* &current, char data, Node* datt){
  if(datt != NULL){
    if(current == NULL){
      current = datt;
      return;
    } else {
      Node* temp = current;
      while(temp->next != NULL){
	temp = temp->next;
      }
      temp->next = datt;
      return;
    }
    
  }
  Node* newNode = new Node(data);
  if(current == NULL){
    current = newNode;

    
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
    cout << current->data << " ";
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


void buildTree(Node* current){
  if(current == NULL){
    return;
  }
  if(isdigit(current->data)){
    push(stackHead, current->data, NULL);
  } else if (!isdigit(current->data)){
    if(stackHead == NULL){
      cout << "invalid expression" << endl;
      return;
    }
    Node* now = new Node(current->data);
    Node* nRight = new Node(peek(stackHead)->data);
    nRight->right = peek(stackHead)->right;
    nRight->left = peek(stackHead)->left;
    now -> right = nRight;
    pop(stackHead);
    if(stackHead == NULL){
      cout << "invalid expression" << endl;
      return;
    }
    Node* nLeft = new Node(peek(stackHead)->data);
    nLeft->right = peek(stackHead)->right;
    nLeft->left = peek(stackHead)->left;
    now->left = nLeft;
    pop(stackHead);

    char temptwo = 'q';
    push(stackHead, temptwo, now);
  }
}


void infix(Node* current){
  if(current != NULL){
    if(isOpp(current->data)){
	cout << "( ";
    }
    infix(current->left);
    cout << current->data << " ";
    infix(current->right);
    if(isOpp(current->data)){
      cout << ")";
    }  
  }
}

void prefix(Node* current){
  if(current != NULL){
    cout << current->data << " ";
    prefix(current->left);
    prefix(current->right);
  }
}


void postfix(Node* current){
  if(current != NULL){
    postfix(current->left);
    postfix(current->right);
    cout << current->data << " ";
  }
}
