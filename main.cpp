#include "avl_tree.h"
#include "generate.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//problem 4 C
void p4(){
	//Random Array
	int* randArr;
	randArr = (int*)malloc(sizeof(int)*5);
	randArr = getRandomArray(5);
	
	//Sorted Array
	int* sortedArr;
	sortedArr = (int*)malloc(sizeof(int)*5);
	sortedArr = getSortedArray(5);
	

	//Insert Random
	cout << "********** Random AVL ***********\n";
	avl_tree randomAVL;
	cout << "Inserting\n";
	for(int i = 0; i < 5; i++){
		cout << "INSERT: " << i << " " << randArr[i] << "  AVL" << endl;
		randomAVL.insertIter(randArr[i]);
	}	
	
	cout << "-------------------\nDELETING\n";
	cout << "DELETE: 0\n";
	randomAVL.deleteIter(0);
	
	cout << "-------------------\nFind Max\n";
	node* max = randomAVL.findMaxIter();
	cout << max->key <<endl;
	cout << "-------------------\nFind Min\n";
	node* min = randomAVL.findMinIter();
	cout << min->key <<endl;
	
	cout << "-------------------\nFind Next\n";
	node* next = randomAVL.findNextIter(min);
	cout << next->key <<endl;
	cout << "-------------------\nFind Previous\n";
	node* previous = randomAVL.findPrevIter(max);
	cout << previous->key <<endl;
	

	//Insert Sorted
	cout << "********** Sorted AVL **********\n";
	avl_tree sortedAVL;
	
	cout << "-------------------\nInserting\n";
	for(int i = 0; i < 5; i++){
		cout << "INSERT: " << i << " " << sortedArr[i] << "  AVL" << endl;
		sortedAVL.insertIter(sortedArr[i]);
	}
	
	cout << "-------------------\nDELETING\n";
	cout << "DELETE: 0\n";
	sortedAVL.deleteIter(0);

	cout << "-------------------\nFind Max\n";
	max = sortedAVL.findMaxIter();
	cout << max->key <<endl;
	cout << "-------------------\nFind Min\n";
	min = sortedAVL.findMinIter();
	cout << min->key <<endl;
	
	cout << "-------------------\nFind Next\n";
	next = sortedAVL.findNextIter(min);
	cout << next->key <<endl;
	cout << "-------------------\nFind Previous\n";
	previous = sortedAVL.findPrevIter(max);
	cout << previous->key <<endl;
	
	
}

void p5A(){
	//Random Array
	int* randArr;
	randArr = (int*)malloc(sizeof(int)*10000);
	randArr = getRandomArray(10000);
		
	//AVL
	//Insert Random
	cout << "********** Random AVL ***********\n";
	avl_tree randomAVL;
	cout << "Inserting\n";
	for(int i = 0; i < 10000; i++){
		cout << "INSERT: " << i << " " << randArr[i] << "  AVL" << endl;
		randomAVL.insertIter(randArr[i]);
	}	

	
	//BST Recursive
	//Insert Random
	cout << "********** Random BST ***********\n";
	bst randomBST;
	cout << "Inserting\n";
	for(int i = 0; i < 10000; i++){
		cout << "INSERT: " << i << " " << randArr[i] << "  BST" << endl;
		randomBST.insertRec(randArr[i]);
	}		
	
	cout << "5 B)\n";
	cout << "BOTH RUN ON MY COMPUTER\n";
	cout << "On a pc with less computing power the recursive calls may crash the program due to the lack of memory available for the calls.\n";
	
}

void p5C(){
	//Random Array
	int* randArr;
	randArr = (int*)malloc(sizeof(int)*10000);
	randArr = getRandomArray(10000);
		
	//AVL
	//Insert Random
	cout << "********** Random AVL ***********\n";
	avl_tree randomAVL;
	cout << "Inserting\n";
	for(int i = 0; i < 10000; i++){
		cout << "INSERT: " << i << " " << randArr[i] << "  AVL" << endl;
		randomAVL.insertIter(randArr[i]);
	}	

	
	//BST Iterative
	//Insert Random
	cout << "********** Random BST ***********\n";
	bst randomBST;
	cout << "Inserting\n";
	for(int i = 0; i < 10000; i++){
		cout << "INSERT: " << i << " " << randArr[i] << "  BST" << endl;
		randomBST.insertIter(randArr[i]);
	}		
	
	
}

void p6B(){
	//Random Array
	int* randArr;
	randArr = (int*)malloc(sizeof(int)*10000);
	randArr = getRandomArray(10000);
		
	//AVL
	//Insert Random
	cout << "********** Random AVL ***********\n";
	int avlCount = 0;
	avl_tree randomAVL;
	cout << "Inserting\n";
	for(int i = 0; i < 10000; i++){
		cout << "INSERT: " << i << " " << randArr[i] << "  AVL" << endl;
		avlCount += randomAVL.insertIterMod(randArr[i]);
	}	

	
	//BST Iterative
	//Insert Random
	cout << "********** Random BST ***********\n";
	int bstCount = 0;
	bst randomBST;
	cout << "Inserting\n";
	for(int i = 0; i < 10000; i++){
		cout << "INSERT: " << i << " " << randArr[i] << "  BST" << endl;
		bstCount += randomBST.insertIterMod(randArr[i]);
	}		
	
	cout << "Levels Traversed:\n";
	cout << "AVL: " << avlCount;
	cout << "\nBST: " << bstCount <<endl;
	
}

void p6C(){
	//Random Array
	int* sortedArr;
	sortedArr = (int*)malloc(sizeof(int)*10000);
	sortedArr = getSortedArray(10000);
		
	//AVL
	//Insert Random
	cout << "********** Random AVL ***********\n";
	int avlCount = 0;
	avl_tree randomAVL;
	cout << "Inserting\n";
	for(int i = 0; i < 10000; i++){
		cout << "INSERT: " << i << " " << sortedArr[i] << "  AVL" << endl;
		avlCount += randomAVL.insertIterMod(sortedArr[i]);
	}	

	
	//BST Iterative
	//Insert Random
	cout << "********** Random BST ***********\n";
	int bstCount = 0;
	bst randomBST;
	cout << "Inserting\n";
	for(int i = 0; i < 10000; i++){
		cout << "INSERT: " << i << " " << sortedArr[i] << "  BST" << endl;
		bstCount += randomBST.insertIterMod(sortedArr[i]);
	}		
	
	cout << "Levels Traversed:\n";
	cout << "AVL: " << avlCount;
	cout << "\nBST: " << bstCount <<endl;
	
}

int main(int argc, char** argv) {
/*
Each of the questions are tested in its respective function.
p4 tests the function calls
p5A tests AVL vs Rec BST
p5C tests AVL vs Iter BST
p6B tests traversals on random array
pcC tests traversals on sorted array
*/



	p4();
	//p5A();
	//p5C();
	//p6B();
	//p6C();
	
	
	
	
	
/*
	int* randArr;
	randArr = (int*)malloc(sizeof(int)*100);
	randArr = getRandomArray(100);
	
	avl_tree randomAVL;
	cout << "Inserting\n";
	for(int i = 0; i < 100; i++){
		cout << "INSERT: " << i << " " << randArr[i] << "  AVL" << endl;
		randomAVL.insertIter(randArr[i]);
	}
	
	randomAVL.printTree();
	
	randomAVL.deleteIter(3);
	
	randomAVL.printTree();
*/

	
	return 0;
}
