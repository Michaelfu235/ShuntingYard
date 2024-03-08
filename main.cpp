//Author: Michael Fu
//Date: 2/27/2024
//Description: this program takes an infix expression and makes it into a postfix expression using a shunting yard algorithm, then puts it into an expression tree. Then it asks the user if they want it in prefix infix or postfix or if they want to put in a new expression or if they want to quit. 

#include <iostream>
#include <cstring>

using namespace std;


//the class node with a data for the character, with a next for use in the queue and stack, and left and right used for the tree
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
  
};

//the head of the Queue and the head of the stack
Node* queueHead = NULL;
Node* stackHead = NULL;

//all the functions neccesary for the queue, stack, tree, and postfix and infix
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
  //justkeepgoing boolean for the repeated loop
  bool justKeepGoing = true;
  while(justKeepGoing){

    //reset queueHead and stackhead to null
    queueHead = NULL;
    stackHead = NULL;

    //input cstring
    char inputt[30];

    //ask the user what expression they want to put in
    cout << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "input a infex expression with only numbers and '+', '-', '*', '/', '^', '(', ')' " << endl;
    cout << "put space between the numbers and expressions" << endl;

    //input the expression
    cin.get(inputt, 30, '\n');
    cin.ignore();

    //shunting yard algorithm:
    //loop through the input, and if its a digit then enqueue it immediatly, if its an open parenthesis then put it to the stack, if its a clothes paraenthesis, then go through the stack and add them to the queue until we reach a closed parenthesis, then pop the closed parenthesis. if the input character[i] isnt a open parenthesis and isnt a digit, then while the stack head isnt null and is an operator and input[i] has more precedence than stackHead, then enqueue the stackhead and pop the stackhead. Lastly, push input[i] onto the stack
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

    //then at the end, put all the things on the stack into the queue
    while(stackHead != NULL){
      enqueue(queueHead, peek(stackHead)->data);
      pop(stackHead);
    }

    //then go through the queue and call the buildtree fuction
    while(queueHead != NULL){
      buildTree(queueHead);
      dequeue(queueHead);
    }

    //then create a new bool of justkeepgoing2 and keep going through, asking if the user wants to get their expression in prefix, infix or postfix, enter a new expressoin or if they want to quit. then call the appropiate function (infix prefix and postfix) or set the looping variables to false depending on the users input.
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

  }
}

//for the queue, if the queueHead is null, set it to the new node, otherwise loop through the queue until you get to the end and set the end to newNode
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

//for the dequeue, if the only item is head, then delete head and set queueHead to null, otherwise replace head with head->next (delete head basically)
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

//for the push function, there are 2 cases: if datt isn't null, and if datt is (this way you can push nodes with only data as well as the node, if there are "next"s attached to the node we want to push. (for future reference, try to make it only take in the node for easier time)
//if datt is a node, set current (stackHead will be the one inputted) to datt if it's null, and otherwise, keep going to the next in the list until it's at the end. Then add datt to the end.
//if datt is null, create a new node with the data, and go through the same process as with datt, but using newNode as the node to be added
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

//for the peek function, keep going until the end of the stack linked list, and just return the last one (as a node)
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


//for the pop function, if theres only 1 element, set stackhead to null, and if not, keep looping through, checking temp->next->next to set temp->next to null if temp->next was the last node. (remove the last element in the linked list of stackhead)
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


//function that gives the precedence of the functions, with ^ being value 3, */ being value 2, and +- being value 1. Otherwise, return 0
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


//function to check if the character given is an operator (for future reference, this can be combined with the precede function, since it gives 0 if the character put into precede isn't a operator)
bool isOpp(char op){
  if(op == '^' || op == '*' || op == '/' || op == '+' || op == '-') {
    return true;
  } else {
    return false;
  }
}


//build tree function
void buildTree(Node* current){

  //if the given node is null (queueHead is null), just return since theres nothing to do
  if(current == NULL){
    return;
  }
  //then if the given current node is a digit, then add it to the stack
  //else if its not a digit, then if stackhead is null, then it's an invalid expression
  if(isdigit(current->data)){
    push(stackHead, current->data, NULL);
  } else if (!isdigit(current->data)){
    if(stackHead == NULL){
      cout << "invalid expression" << endl;
      return;
    }
    //if the expression is valid, then create a temp node now using the data (the operator)
    Node* now = new Node(current->data);
    //nRight is a new temp node that uses the data from the last element of stack
    Node* nRight = new Node(peek(stackHead)->data);

    //set nRight to the peek(stack)'s right and nLeft to it's left and set now's right to nRight
    nRight->right = peek(stackHead)->right;
    nRight->left = peek(stackHead)->left;
    now -> right = nRight;
    //then pop stack
    pop(stackHead);
    if(stackHead == NULL){
      //if stackHead is now null, then that means the expression was invalid (numbers and operators dont add up)
      cout << "invalid expression" << endl;
      return;
    }

    //do the same thing as above with nRight, but using nLeft
    Node* nLeft = new Node(peek(stackHead)->data);
    nLeft->right = peek(stackHead)->right;
    nLeft->left = peek(stackHead)->left;
    now->left = nLeft;
    pop(stackHead);

    
    char temptwo = 'q';
    push(stackHead, temptwo, now);
  }
}


//for the infix, print out a left parenthesis before each operator and the number, and a right parenthesis after each operator and the number, 
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

//for the prefix, print out the operator, then recursively call the function again so that it prints out the numbers at the end of the function
void prefix(Node* current){
  if(current != NULL){
    cout << current->data << " ";
    prefix(current->left);
    prefix(current->right);
  }
}


//for the postfix, print out the two parts of the operator, then the operator and recursively call the function 
void postfix(Node* current){
  if(current != NULL){
    postfix(current->left);
    postfix(current->right);
    cout << current->data << " ";
  }
}
