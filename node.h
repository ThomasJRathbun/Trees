#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;
//NODE CLASS
class node {
public:
	node* l;
	node* r;
	node* p;
	int key;
	int height;
	node(int, node*);
	void printNode();
	node* createNode(int, node*);
};

//NODE FUNCTIONS
//Constructor
node::node(int key, node* p) {
	l = NULL;
	r = NULL;
	p = p;
	key = key;
};

node* createNode(int key, node* p) {
	node* temp = new node(key, p);
	temp->l = NULL;
	temp->r = NULL;
	temp->p = p;
	temp->key = key;
	return temp;
};

void node::printNode() {
	cout << key << endl;
};

#endif
