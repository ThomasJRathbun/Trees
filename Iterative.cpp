#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;


#define USEDEBUG
//Debug
#ifdef USEDEBUG
#define Debug(x) std::cout << x
#else
#define Debug(x) 
#endif 


int* getRandomArray(int n){
  srand(time(NULL));
	
  vector<int> v;
  int* r = new int(n);
  for(int i =0; i < n*5; i++){
    v.push_back(i);	
  }
	
  for(int i =0; i < n; i++){
    int x = rand() % v.size();
    r[i] = v[x];
    v.erase(v.begin()+x);
  }
	
  return r;
}

int* getSortedArray(int n){
  int* r = new int(n);
  for(int i=0; i<n; i++)
    r[i] = n - i;
  return r;
};





typedef struct Node{
  Node* left;
  Node* right;
  Node* parent;
  int value;
	
}Node;

void printNode(Node*);
Node* createNode(Node*, Node*, int);
Node* insertIter(Node*,int);
Node* deleteIter(Node*, int);
Node* findNextIter(Node*);
Node* findPrevIter(Node*);
Node* findMinIter(Node*);
Node* findMaxIter(Node*);

void printNode(Node* node){
  cout << node->value <<endl;
};

Node* createNode(Node* p,int n ){
  Node* temp = new Node;
  temp->left = NULL;
  temp->right = NULL;
  temp->parent = p;
  temp->value = n;
  return temp;
};

Node* insertIter(Node* node, int n){
  Node* curr = node;
  Node* last = NULL;
	
  while(curr != NULL){
    last = curr;
    if(n < curr->value)
      curr = curr->left;
    else
      curr = curr->right;
  }
  if(!last)
    last =  createNode(NULL,n);
  else if ( n < last->value)
    last->left = createNode(last,n);
  else
    last->right = createNode(last,n);
	
  return last;
};

Node* findMinIter(Node* node){
  Node* curr = node;
  while (curr->left)
    curr = curr->left;
  return curr;
};

Node* findMaxIter(Node* node){
  Node* curr = node;
  while(curr->right)
    curr = curr->right;
  return curr;	
	
};

Node* findNextIter(Node* node){
  Node* curr = node;
  Node* pare = node->parent;
	
	
  if(curr->right)
    return findMinIter(curr->right);
  else{
    while(curr && pare){
      if(curr == pare->left)
	return pare;
      else{
	curr = pare;
	pare = pare->parent;
      }			
    }		
  }
  return pare;
};

Node* findPrevIter(Node* node){
  Node* curr = node;
  Node* pare = node->parent;
	
  if(curr->left)
    return findMaxIter(curr->left);
  else{
    while(curr && pare){
      if(curr == pare->right)
	return pare;
      else{
	curr = pare;
	pare = pare->parent;
      }			
    }		
  }
  return pare;
};

void sort(Node* node){
  Node* s = findMinIter(node);
  Node* e = findMaxIter(node);
  
  while(s){
    printNode(s);
    s = findNextIter(s);
  }
};

Node* deleteIter(Node* node, int n){
  Node* curr = node;
  Node* last;

  //Find Node
  while(curr){
    last = curr;
    if(n < curr->value)
      curr = curr->left;
    else
      curr = curr->right;
  }

  if(!last){
    return NULL;
  }
  Node* parent = last->parent;
  //Case 1
  if(!last->left && !last->right){
    last = NULL;
  }
  //Case 2
  else if(last->left && !last->right){
    if(parent->left == last){
      parent->left = last->left;
      last->left->parent = parent;
    }
    else{
      parent->right = last->right;
      last->right->parent = parent;
    }
  }
  //Case 3
  else if (last->left && last->right){
    Node* succ = findNextIter(last);

    if(!succ->right){
      succ->left = last->left;
      succ->right = last->right;
      succ->parent = last->parent;
      free(last);
      return succ;
    }
    else{
      succ->parent->left = succ->right;
      succ->right->parent = succ->parent;
      succ->left = last->left;
      succ->right = last->right;
      succ->parent = node->parent;
      free(last);
      return succ;
    }
  }
  return last;
};

int main(){
  int* a;
  int* b;
	
  Node* root = NULL;
  a = getRandomArray(5);
  b = getSortedArray(5);
  cout << "INSERT ROOT"<<endl;
  root = insertIter(root,a[0]);
  printNode(root);

  cout << "INSERT REST"<<endl;
  for( int i =1; i<5;i++){
    cout << a[i] << endl;
    insertIter(root,a[i]);
  }
  cout << "ROOT"<<endl;
  printNode(root);
  cout << "MAX" <<endl;
  printNode(findMaxIter(root));
  cout << "MIN" <<endl;
  printNode(findMinIter(root));
	
  Node* n = findMaxIter(root);
  for(int i =0; i < 5; i++){
    cout << "i: ";
    printNode(n);
    n = findPrevIter(n);	
  }

  sort(root);
  return 0;
}










