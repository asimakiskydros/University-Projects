#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
using namespace std;

struct node{
	char *data;
	int instances;
	node *left,*right;
};

class BinarySearchTree{
	protected:
		node *root;
		void insert(char*,node*);
		node *search(char*,node*);
		void destroy(node*);
		void print(node*,ostream &);
		void scan(node*,short,ostream &);//short: 1;preorder 2;inorder 3;postorder
		node *parent(char*,node*, bool* /*isRight*/);
	public:
		BinarySearchTree();//Creates empty tree
		~BinarySearchTree();
		virtual void insert(char *);
		bool search(char *,ostream &);//Searches for string, if it exists
		//it prints its details and returns true, else it returns false
		void reset();//Resets the tree to an empty one (deletes everything and sets root to NULL)
		virtual bool remove(char *);//Finds then deletes the specified string
		//then returns true - if it doesnt exist it returns false
		void preorder(ostream &);
		void inorder(ostream &);
		void postorder(ostream &);
		char* get_max();//Finds and returns the MAX value 
		char* get_min();//The exact same thing but for the MIN value
};

#endif //BINARYSEARCHTREE_H