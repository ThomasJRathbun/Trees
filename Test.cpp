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

void printNode(Node*);
Node* createNode(int, Node*);
Node* deleteRec(Node*, int);
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
	
	if ( n > node->value ){ 
		node->right = insertRec(node->right, n);
		node->right->parent = node;
	}
	else{ // Default: place duplicates on left branch
	  node->left = insertRec(node->left, n);

		node->left->parent = node;
	}	
	return node;
};

Node* deleteRec(Node* node, int n){
	//Hibbard Deletion
	//http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete.html
	//Textbook
  if(n < node->value && node->left){
    cout  << "Node is LESS"<<endl;
    node->left = deleteRec(node->left,n);
    return node;
  }
  else if( n > node->value && node->right){
    cout  << "Node is Greater"<<endl;
    node->right = deleteRec(node->right,n);
    return node;
  }
    else if (n == node->value){
      if(!node->left && !node->right){
	cout << "CASE 1"<<endl;
	return NULL;
      }
      else if(node->left && !node->right){
	cout << "CASE 2" <<endl;
	return node->left;
      }
      else if(node->right && !node->left){
	cout << "CASE 2" <<endl;
	return node->right;
      }
      else if(node->right && node->left){
	Node* succ = findNextRec(node);
	Node* parent = succ->parent;
	if(!succ->right){
	  succ->left = node->left;
	  succ->right = node->right;
	  succ->parent = node->parent;
	  free(node);
	  return succ;
	}
	else{
	  succ->parent->left = succ->right;
	  succ->right->parent = succ->parent;
	  succ->left = node->left;
	  succ->right = node->right;
	  succ->parent = node->parent;
	  free(node);
	  return succ;
	}
	  
      }
	
    }
  return node;
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
	cout << "MAX: " << (aa->value)<<endl;
	cout << "MIN: " << (ab->value)<<endl;	
	
	cout << "NEXT: " << (findNextRec(ab))->value <<endl;
	cout << "DELETE" <<endl;
	root = deleteRec(root,aa->value);
	aa = findMaxRec(root);
	
	cout << "MAX: " << (aa->value)<<endl;
	cout << "DELETE" <<endl;	
	root = deleteRec(root,ab->value);
	
	ab = findMinRec(root);
	cout << "Min: " << (ab->value)<<endl;
	aa = findMaxRec(root);
	cout << "Max: " << (aa->value)<<endl;

	int x = 0;
	cin >> x;
	root = deleteRec(root,x);
}
