#ifndef BINARYSEARCHTREEAVL_H
#define BINARYSEARCHTREEAVL_H
#include "BinarySearchTree.h"

class BinarySearchTreeAVL:public BinarySearchTree{
	private:
		int treeHeight(node*);
		int heightDiff(node*);
		bool scanForUnbalance(node*,node* /*parent*/,bool /*isRight*/);
		void leftRotation(node*, node* /*parent*/,bool /*isRight*/);
		void rightRotation(node*, node* /*parent*/,bool /*isRight*/);
	public:
		BinarySearchTreeAVL();
		void insert(char *);
		bool remove(char *);
		//These two behave exactly the same as in the regular tree, but with every
		//instance they check if the height balance is disturbed and act accordingly
};

#endif //BINARYSEARCHTREEAVL_H