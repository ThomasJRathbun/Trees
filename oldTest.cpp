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

typedef struct Node{
	Node* left;
	Node* right;
	Node* parent;
	int value;
	
}Node;


Node* createNode(int, Node*);
void deleteRec(Node*, int);
Node* findNextRec(Node*);
Node* findMinRec(Node*);
Node* findMaxRec(Node*);



Node* createNode(int n, Node* p ){
	Node* temp = new Node;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = p;
	temp->value = n;
	return temp;
};

Node* insertRec(Node* node, int n){
	if (node == NULL)
		return createNode(n,NULL);
	
	Node* temp;
	if ( n > node->value ){ 
		temp = insertRec(node->right, n);
		node->right = temp;
		temp->parent = node;
	}
	else{ // Default: place duplicates on left branch
		temp = insertRec(node->left, n);
		node->left = temp;
		temp->parent = node;
	}	
	return node;
};

void deleteRec(Node* node, int n){
	//Hibbard Deletion
	//http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete.html
	//Textbook
	cout  << "DELETE"<<endl;
	//Tree is NULL
	if(node == NULL)
		return;
	
	//Found the Node
	if (n == node->value){
		cout << "FOUND NODE" <<endl;
		//Case 1 No subtree
		if(node->parent->left == NULL && node->parent->right == NULL){
			cout  << "CASE 1"<<endl;
			if(n < node->parent->value)
				node->parent->left  = NULL;
			else
				node->parent->right = NULL;
		}
		//Case 2 One subtree
		else if(node->left){
			cout  << "CASE 2"<<endl;
			if(n < node->parent->value)
				node->parent->left  = node->left;
			else
				node->parent->right = node->left;
		}
		else if(node->right){
			if(n < node->parent->value)
				node->parent->left  = node->right;
			else
				node->parent->right = node->right;
		}
		
		//Case 3
		else{
			cout  << "CASE 3"<<endl;
			
			Node* temp = findNextRec(node);
			
			if(node->parent == NULL){
				node = temp;
				temp->parent->left = temp->right;
				temp->left =
				temp->parent = NULL;
				
			}
			
			

			if(n < node->parent->value)
				node->parent->left  = temp;
			else
				node->parent->right = temp;	
			
			if(temp->value < temp->parent->value)
				temp->parent->left  = NULL;
			else
				temp->parent->right = NULL;	
				
			temp->parent = node->parent;
			
			free(node);	
		}
		return;
	}
	//Recure down the tree
	else if(n < node->value && node->left){
		cout  << "Node is LESS"<<endl;
		deleteRec(node->left,n);
	}
	else{
		cout  << "Node is Greater"<<endl;
		if (node->right == NULL)
			return;
		deleteRec(node->right,n);
	}
};

Node* findNextRec(Node* node){
	if (node->right == NULL){
		if(node->parent == NULL)
			return NULL;
		Node* curr = node->parent;
		while(curr!= NULL && node != curr->left){
			node = curr;
			curr = curr->parent;			
		}
		return curr;
	}	
	else{
		return findMinRec(node->right);
	}
};

Node* findPrevRec(Node* node){
	if (node->left == NULL){
		if(node->parent == NULL)
			return NULL;
		Node* curr = node->parent;
		while(curr!= NULL && node != curr->right){
			node = curr;
			curr = curr->parent;			
		}
		return curr;
	}	
	else{
		return findMaxRec(node->left);
	}
};

void printNode(Node* node){
	cout << node->value <<endl;
};

Node* findMinRec(Node* node){
	if(node->left == NULL)
		return node;
	else
		return findMinRec(node->left);
}

Node* findMaxRec(Node* node){
	if(node->right == NULL)
		return node;
	else
		return findMaxRec(node->right);
};


/*
//ITERATIVE
void insertIter(int n){
	Node* curr;
	while( n <= value || n > value){
		if(n > value){
			if(right)
				curr = right;
			else{
				curr = new Node(value, curr);
				return;
			}
		}
		else{
			if(left)
				curr = left;
			else{
				left = new Node(value, curr);
				return;
			}
		}
	}
};

void deleteIter(int n){
	Node* curr;
	while( n <= value || n > value){
		if (n == value){
			curr = NULL;
			return;
		}
		if(n > value && right)
			curr = right;	
		else if ( n < value && left)
			curr = left;
		else
			return;
	}
};

Node* findMinIter(){
	Node* curr;
	while ( left)
		curr = left;
	return curr;

}

Node* findMaxIter(){
	Node* curr;
	while(right)
		curr = right;
	return curr;
};

*/

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
}

int main(){
	int* a;
	int* b;
	
	Node* root = NULL;
	a = getRandomArray(5);
	b = getSortedArray(5);
	
	for( int i =0; i<5;i++){
		root = insertRec(root,a[i]);
		cout << a[i] << endl;
	}
	
	for( int i =0; i<5;i++){
		cout << b[i] << endl;
	}
	cout << "************"<<endl;
	cout << root->value <<endl;
	cout << "                 "<<endl;
	Node* aa = findMaxRec(root);
	Node* ab = findMinRec(root);
	cout << "MAX: " << (aa->value)<<endl;
	cout << "MIN: " << (ab->value)<<endl;
	
	
	Node* n = findMinRec(root);
	for(int i =0; i < 5; i++){
		cout << "i: ";
		printNode(n);
		n = findNextRec(n);	
	}
	
	n = findMaxRec(root);
	for(int i =0; i < 5; i++){
		cout << "i: ";
		printNode(n);
		n = findPrevRec(n);	
	}
	
	
	cout << "NEXT: " << (findNextRec(ab))->value <<endl;
	
	deleteRec(root,aa->value);
	aa = findMaxRec(root);
	
	cout << "MAX: " << (aa->value)<<endl;
	deleteRec(root,ab->value);
	
	ab = findMinRec(root);
	cout << "Min: " << (ab->value)<<endl;
}
