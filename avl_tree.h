#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <time.h>
#include <vector>
#include "node.h"

using namespace std;

//AVL CLASS
class avl_tree {
	//Utility
	int height(node*);
	int balanceFactor(node*);
	void balance(node*);
	void ll_rotate(node*);
	void lr_rotate(node*);
	void rr_rotate(node*);
	void rl_rotate(node*);
	node* findMaxIter(node*);
	node* findMinIter(node*);
	void  transplant(node*,node*);
	//Recursive Functions
	node* insertRec(int, node*);

	//Iterative Functions
	//void  insertIter(int);
	
public:
	node* root;
	avl_tree();
	void insertRec(int);
	void insertIter(int);
	int insertIterMod(int);
	void deleteIter(int);
	void printTree();
	void printLevel(node*, int);
	int height();
	void deleteIter(node*, int);
	node* findMaxIter();
	node* findMinIter();
	node* findNextIter(node*);
	node* findPrevIter(node*);

};

//Constructor for AVL_Tree
avl_tree::avl_tree() {
	root = NULL;
};

node* avl_tree::findMaxIter(){
	return findMaxIter(this->root);
}
node* avl_tree::findMinIter(){
	return findMinIter(this->root);
}


//UTILITY
//Call when Right Heavy
void avl_tree::rr_rotate(node* root) {
	//Select Nodes to be moved
	//The Top node: A
	node* A = root;
	//Right Child of A: B
	node* B = A->r;
	//Left Child of B: Bl
	node* Bl = B->l; // Bl is the only child of B that changes when rotating to the Left
	
	//Rotate
	B->l = A;
	A->r = Bl;
	if(Bl)
		Bl->p = A;
		
	//Change Parents 
	if(A->p == NULL){  // If A was the root Set B to the Root
		B->p = NULL;
		this->root = B;
	}
	else{
		B->p = A->p;	
		if(B->key < A->p->key)
			A->p->l = B;
		else
			A->p->r = B;	
	}

	A->p = B;


};

//Call when Left Heavy
void avl_tree::ll_rotate(node* root){
	//Select Nodes to be moved
	//The Top node: A
	node* A = root;
	//Left Child of A: B
	node* B = A->l;
	//Right Child of B: Bl
	node* Br = B->r;


	//Rotate
	A->l = Br;
	if(Br)
		Br->p = A;
	
	B->r = A;


	//Change Parents 
	if(A->p == NULL){ // If A was the root Set B to the Root
		B->p = NULL;
		this->root = B;
	}
	else{
		B->p = A->p;	
		if(B->key < A->p->key)
			A->p->l = B;
		else
			A->p->r = B;	
	}

	A->p = B;

};

//If Left Right Heavy
void avl_tree::lr_rotate(node* root) {
	rr_rotate(root->l);
	ll_rotate(root);
};

//If Right Left Heavy
void avl_tree::rl_rotate(node* root) {
	ll_rotate(root->r);
	rr_rotate(root);
};

//Public Call to Height
int avl_tree::height() {
	if (root)
		return height(root);
	else
		return 0;
};


int avl_tree::height(node* root) {
	//height counter
	int h = 0;

	if (!root)
		return 0;
	
	//Hold nodes at a given level starting with root
	queue<node*> nodeQ;
	nodeQ.push(root);
	
	while (1) {
		
		/*Keep track of the number of nodes in the Q FOR EACH LEVEL
		nodes only keeps track of how many nodes are at a given level. 
		The Queue should be populated each round with the children of 
		the nodes at each level. Once A leevel has no children the Q 
		will be empty*/
		int nodes = nodeQ.size();
		
		//If No nodes at a given level have a child return the height of the tree
		if (nodes == 0)
			return h;
		
		//Increase tree height
		h++;

		while (nodes > 0) {
			//Check if a node has children, if it does add them to the Q and decrement the number
			node* front = nodeQ.front();
			nodeQ.pop();
			if (front->l != NULL)
				nodeQ.push(front->l);
			if (front->r != NULL)
				nodeQ.push(front->r);
			nodes--;
		}
	}
}

int avl_tree::balanceFactor(node* root) {
	/*Subtract height of level from height of right*/
	int hl = height(root->l);

	int hr = height(root->r);
	
	return (hl - hr);
};

void avl_tree::balance(node* root) {
	int bf = balanceFactor(root);
	if (bf < -1) {
		//Subtree is Right Heavy
		if (balanceFactor(root->r) < 0) {
			rr_rotate(root);
		}
		else {
			//Subtree is Right Left Heavy
			rl_rotate(root);
		}

	}
	else if (bf > 1) {
		//Subtree is Left Heavy
		if (balanceFactor(root->l) > 0) {
			ll_rotate(root);
		}
		else {
		//Subtree is Left Right Heavy
			lr_rotate(root);
		}
	}
	else
		return;
};

//RECURSION
void avl_tree::insertRec(int key) {
	root = insertRec(key, root);
};

node* avl_tree::insertRec(int key, node* root) {
	//If root is null insert to root
	if (!root) {
		return createNode(key, NULL);
	}

	//Traverse tree to inserting spot
	if (key < root->key) {
		if (root->l)
			root->l = insertRec(key, root->l);
		else
			root->l = createNode(key, root);
	}
	else {
		if (root->r)
			root->r = insertRec(key, root->r);
		else
			root->r = createNode(key, root);
	}
	
	//After insertion Balance Tree
	balance(root);

	return root;
};

//ITERITIVE
void avl_tree::insertIter(int key) {
	node* curr = this->root;
	node* last = curr;
	
	//If Root is NULL insert at Root
	if(!curr){
		this->root = createNode(key,NULL);
		return;
	}
	
	//Traverse to insertion point
	while (curr) {
		last = curr;
		if (key < curr->key){
			if(curr->l)
				curr = curr->l;
			else{
				curr->l = createNode(key,last);
				break;
			}
		}
		else{
			if(curr->r)
				curr = curr->r;
			else{
				curr->r = createNode(key,last);
				break;
			}
		}
	}

	//Balance tree from parent of insertion up to the root
	while (curr) {
		balance(curr);
		curr = curr->p;
	}

}

int avl_tree::insertIterMod(int key) {
	int count = 0;
	node* curr = this->root;
	node* last = curr;
	if(!curr){
		this->root = createNode(key,NULL);
		return 0;
	}
	while (curr) {
		last = curr;
		if (key < curr->key){
			if(curr->l){
				curr = curr->l;
				count++;
			}
			else{
				curr->l = createNode(key,last);
				break;
			}
		}
		else{
			if(curr->r){
				curr = curr->r;
				count++;
			}
			else{
				curr->r = createNode(key,last);
				break;
			}
		}
	}

	while (curr) {
		balance(curr);
		curr = curr->p;
	}
	return count;
}

node* avl_tree::findMinIter(node* root){
//Follow Left Branch to min value
  node* curr = root;
  while (curr->l)
    curr = curr->l;
  return curr;
};

node* avl_tree::findMaxIter(node* root){
	//Follow right Branch to max value
  node* curr = root;
  while(curr->r)
    curr = curr->r;
  return curr;	
	
};

node* avl_tree::findNextIter(node* root){
  node* curr = root;
  node* pare = root->p;
	
	
  if(curr->r)
    return findMinIter(curr->r);
  else{
    while(curr && pare){
      if(curr == pare->l)
	return pare;
      else{
	curr = pare;
	pare = pare->p;
      }			
    }		
  }
  return pare;
};

node* avl_tree::findPrevIter(node* root){
  node* curr = root;
  node* pare = root->p;
	
  if(curr->l)
    return findMaxIter(curr->l);
  else{
    while(curr && pare){
      if(curr == pare->r)
	return pare;
      else{
	curr = pare;
	pare = pare->p;
      }			
    }		
  }
  return pare;
};

void avl_tree::deleteIter(int key){
	deleteIter(this->root, key);
};


void avl_tree::transplant(node* root, node* newRoot){
	//if root is being replaced swap root with newRoot
	if(!root->p){
		this->root = newRoot;
	}
	//if node being deleted is the left of parent
	//node being swapped should be the child of the left
	else if (root->p->l && root->key == ((root->p)->l)->key){
		root->p->l = newRoot;
	}
	//if node being deleted is the right of parent
	//node being swapped should be the child of the right
	else{
		root->p->r = newRoot;
	}
	//set new nodes parent to the parent of the deleted node
	if(newRoot)
		newRoot->p = root->p; 
	}

void avl_tree::deleteIter(node* root, int key){
	node* curr = root;
	//traverse to deletion point
	while(curr->key != key){
		if(curr->key == key)
			break;
		if(key < curr->key){
			if(curr->l)
				curr = curr->l;
			else
				cout << key << " Does not exist!\n";
		}
		else{
			if(curr->r)
				curr = curr->r;
			else
				cout << key << " Does not exist!\n";
		}
	}
		if(curr->key == key){
			//If deleted node doesn't have a left child transplant the right
			if(!curr->l){
				transplant(curr,curr->r);
		}
		//If deleted node doesn't have a right child transplant the left
			else if(!curr->r){
				transplant(curr,curr->l);
			}
			//If deletd node has both children replace it with the successor
			else{
				node* min = findMinIter(curr->r);
				if(min->p->key != curr->key){
					transplant(min,min->r);
					min->r = curr->r;
					min->r->p = min;
				}
				transplant(curr,min);
				min->l = curr->l;
				min->l->p = min;	
			}
		}
		else
			cout << key << " Does not exist!\n";
		//Set the current node to the parent of the deleted node
		curr = curr->p;
		
		//Balance
		while (curr) {
			balance(curr);
			curr = curr->p;
		}	
		
};



//BST
class bst{
	//Utility
	void  sort(node*);

	//Recursive Functions
	node* insertRec(node*, int);
	node* deleteRec(node*, int);
	node* findNextRec(node*);
	node* findPrevRec(node*);
	node* findMinRec(node*);
	node* findMaxRec(node*);

	//Iterative Functions
	//node* insertIter(node*,int);
	void deleteIter(node*, int);
	void  transplant(node*,node*);
	node* findNextIter(node*);
	node* findPrevIter(node*);
	node* findMinIter(node*);
	node* findMaxIter(node*);
	
		
public:
	node* root;
	bst();
	node* findMaxRec();
	node* findMinRec();
	node* findMaxIter();
	node* findMinIter();
	void printNode(node*);
	void insertRec(int);
	void deleteRec(int);
	void insertIter(int);
	void deleteIter(int);
	int insertIterMod(int);
	void sort();
	
};
//Public
bst::bst(){
	root = NULL;
}
void bst::sort(){
	sort(this->root);
}
void bst::insertRec(int n){
	this->root = insertRec(this->root,n);	
};

void bst::deleteRec(int n){
	this->root = deleteRec(this->root,n);	
};

node* bst::findMaxRec(){
	return findMaxRec(this->root);
}
node* bst::findMinRec(){
	return findMinRec(this->root);
}
//BST FUNCTIONS
node* bst::insertRec(node* root, int n){
	if (root == NULL)
		return createNode(n,NULL);
	
	if ( n > root->key ){ 
		root->r = insertRec(root->r, n);
		root->r->p = root;
	}
	else{ // Default: place duplicates on left branch
	  root->l = insertRec(root->l, n);
		root->l->p = root;
	}	
	return root;
};

node* bst::deleteRec(node* root, int n){
	//Hibbard Deletion
	//http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete.html
	//Textbook
  if(n < root->key && root->l){
    root->l = deleteRec(root->l,n);
    return root;
  }
  else if( n > root->key && root->r){
    root->r = deleteRec(root->r,n);
    return root;
  }
    else if (n == root->key){
      if(!root->l && !root->r){
	return NULL;
      }
      else if(root->l && !root->r){
	return root->l;
      }
      else if(root->r && !root->l){
	return root->r;
      }
      else if(root->r && root->l){
	node* succ = findNextRec(root);
	node* parent = succ->p;
	if(!succ->r){
	  succ->l = root->l;
	  succ->r = root->r;
	  succ->p = root->p;
	  free(root);
	  return succ;
	}
	else{
	  succ->p->l = succ->r;
	  succ->r->p = succ->p;
	  succ->l = root->l;
	  succ->r = root->r;
	  succ->p = root->p;
	  free(root);
	  return succ;
	}
	  
      }
	
    }
  return root;
};

node* bst::findNextRec(node* root){
	if (root->r == NULL){
		if(root->p == NULL)
			return NULL;
		node* curr = root->p;
		while(curr!= NULL && root != curr->l){
			root = curr;
			curr = curr->p;			
		}
		return curr;
	}	
	else{
		return findMinRec(root->r);
	}
};

node* bst::findPrevRec(node* root){
	if (root->l == NULL){
		if(root->p == NULL)
			return NULL;
		node* curr = root->p;
		while(curr!= NULL && root != curr->r){
			root = curr;
			curr = curr->p;			
		}
		return curr;
	}	
	else{
		return findMaxRec(root->l);
	}
};

void bst::printNode(node* root){
	cout << root->key <<endl;
};

node* bst::findMinRec(node* root){
	if(root->l == NULL)
		return root;
	else
		return findMinRec(root->l);
}

node* bst::findMaxRec(node* root){
	if(root->r == NULL)
		return root;
	else
		return findMaxRec(root->r);
};

void bst::sort(node* root){
	node* s = findMinRec(root);
	node* e = findMaxRec(root);
	
	while (s != e){
		printNode(s);
		s = findNextRec(s);
	}	
		printNode(e);
};

//ITERITIVE
//PUBLIC
node* bst::findMaxIter(){
	return findMaxIter(this->root);
};

node* bst::findMinIter(){
	return findMinIter(this->root);
};

int bst::insertIterMod(int n){
  int count = 0;	
  node* curr = this->root;
  node* last = NULL;
	
  while(curr != NULL){
    last = curr;
    if(n < curr->key){
      curr = curr->l;
  	  count++;
  	}
    else{
      curr = curr->r;
      count++;
	}
  }
  if(!this->root)
    this->root = createNode(n,NULL);
  else if ( n < last->key)
    last->l = createNode(n,last);
  else
    last->r = createNode(n,last);

	return count;
}


void bst::insertIter(int n){
  node* curr = this->root;
  node* last = NULL;
	
  while(curr != NULL){
    last = curr;
    if(n < curr->key)
      curr = curr->l;
    else
      curr = curr->r;
  }
  if(!this->root){
    this->root = createNode(n,NULL);
    this->root->p = NULL;
	}
  else if ( n < last->key)
    last->l = createNode(n,last);
  else
    last->r = createNode(n,last);
	
  //return last;
};

node* bst::findMinIter(node* root){
  node* curr = root;
  while (curr->l)
    curr = curr->l;
  return curr;
};

node* bst::findMaxIter(node* root){
  node* curr = root;
  while(curr->r)
    curr = curr->r;
  return curr;	
	
};

node* bst::findNextIter(node* root){
  node* curr = root;
  node* pare = root->p;
	
	
  if(curr->r)
    return findMinIter(curr->r);
  else{
    while(curr && pare){
      if(curr == pare->l)
	return pare;
      else{
	curr = pare;
	pare = pare->p;
      }			
    }		
  }
  return pare;
};

node* bst::findPrevIter(node* root){
  node* curr = root;
  node* pare = root->p;
	
  if(curr->l)
    return findMaxIter(curr->l);
  else{
    while(curr && pare){
      if(curr == pare->r)
	return pare;
      else{
	curr = pare;
	pare = pare->p;
      }			
    }		
  }
  return pare;
};
void bst::deleteIter(int key){
	deleteIter(this->root, key);
};

void bst::transplant(node* root, node* newRoot){
	if(!root->p){
		this->root = newRoot;
	}
	else if (root->p->l && root->key == ((root->p)->l)->key){
		root->p->l = newRoot;
	}
	else{
		root->p->r = newRoot;
	}
	if(newRoot)
		newRoot->p = root->p; 
	}

void bst::deleteIter(node* root, int key){
	node* curr = root;
	while(curr->key != key){
		if(curr->key == key)
			break;
		if(key < curr->key){
			if(curr->l)
				curr = curr->l;
			else
				cout << key << " Does not exist!\n";
		}
		else{
			if(curr->r)
				curr = curr->r;
			else
				cout << key << " Does not exist!\n";
		}
	}
		if(curr->key == key){
			if(!curr->l){
				transplant(curr,curr->r);
		}
			else if(!curr->r){
				transplant(curr,curr->l);
			}
			else{
				node* min = findMinIter(curr->r);
				if(min->p->key != curr->key){
					transplant(min,min->r);
					min->r = curr->r;
					min->r->p = min;
				}
				transplant(curr,min);
				min->l = curr->l;
				min->l->p = min;	
			}
		}
		else
			cout << key << " Does not exist!\n";
};
#endif


