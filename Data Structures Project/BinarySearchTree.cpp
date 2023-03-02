#include "BinarySearchTree.h"
#include <cstring>
#include <iostream>

using namespace std;

BinarySearchTree::BinarySearchTree(){
	root=nullptr;
}
BinarySearchTree::~BinarySearchTree(){
	destroy(root);
}
void BinarySearchTree::reset(){
	destroy(root);
	root=nullptr;
}
void BinarySearchTree::destroy(node *ptr){
	if(ptr!=nullptr){
		destroy(ptr->left);
		destroy(ptr->right);
		delete [] ptr->data;
	}
	delete ptr;
}
//Public part - the user can't be expected to provide a node
void BinarySearchTree::insert(char *string){
	if(root!=nullptr){//if the root exists, the tree exists; kickstart the recursion
		insert(string,root);
	}
	else{//the root is empty; place at root
		root=new node;
		root->data=new char[strlen(string)+1];
		strcpy(root->data,string);
		root->left=nullptr;
		root->right=nullptr;
		root->instances=1;
	}
}
//Private part - the node is necessary for the recursive method
void BinarySearchTree::insert(char *string,node *ptr){
	int comparator=strcmp(string,ptr->data);
	if(comparator==0)//Identical strings occupy the same node multiple times
		ptr->instances++;
	else if(comparator<0){//i.e. if string<ptr->data
		if(ptr->left!=nullptr){
			int comp=strcmp(string,ptr->left->data);
			if(comp!=0)//The node is occupied by a foreign string, continue searching	
				insert(string,ptr->left);
			else//Occupied, but by the same string
				ptr->left->instances++;
		}
		else{//Available space, place here
			ptr->left=new node;
			ptr->left->data=new char[strlen(string)+1];
			strcpy(ptr->left->data,string);
			ptr->left->left=nullptr;
			ptr->left->right=nullptr;
			ptr->left->instances=1;
		}
	}
	else if(comparator>0){//i.e. if string>ptr->data
		if(ptr->right!=nullptr){
			int comp=strcmp(string,ptr->right->data);
			if(comp!=0)//The node is occupied by a foreign string, continue searching	
				insert(string,ptr->right);
			else//Occupied, but by the same string
				ptr->right->instances++;
		}
		else{//Available space, place here
			ptr->right=new node;
			ptr->right->data=new char[strlen(string)+1];
			strcpy(ptr->right->data,string);
			ptr->right->left=nullptr;
			ptr->right->right=nullptr;
			ptr->right->instances=1;
		}
	}
}
//Private part - same logic
node* BinarySearchTree::search(char* string,node* ptr){
	if(ptr!=nullptr){
		int comparator=strcmp(string,ptr->data);
		if(comparator==0)//string==ptr->data
			return ptr;
		else if(comparator<0)//string<ptr->data
			return search(string,ptr->left);
		else//string>ptr->data
			return search(string,ptr->right);
	}
	return nullptr;
}
//Public part
bool BinarySearchTree::search(char* string,ostream &o){
	node* ptr=search(string,root);
	if(ptr!=nullptr)
		o<<">>\""<<ptr->data<<"\" found "<<ptr->instances<<" time(s)"<<endl;
	return ptr!=nullptr;
}
char *BinarySearchTree::get_max(){
	//As this is a binary Search tree, the maximum value is the furthermost leaf on the right
	node *temp;
	temp=root;
	while(temp->right!=nullptr)
		temp=temp->right;
	return temp->data;
}
char *BinarySearchTree::get_min(){
	//As expected, the furthermost leaf on the left is the minimum value
	node *temp;
	temp=root;
	while(temp->left!=nullptr)
		temp=temp->left;
	return temp->data;
}
void BinarySearchTree::print(node* ptr,ostream &o){
	int times=ptr->instances;
	o<<"	"<<ptr->data;
	if(times>1)
		o<<"(*"<<times<<")";
	o<<endl;
}
void BinarySearchTree::scan(node* ptr,short which,ostream &o){
	if(ptr==nullptr)
		return;
	if(which==1){//preorder; Root->Left->Right
		print(ptr,o);
		scan(ptr->left,1,o);
		scan(ptr->right,1,o);
	}
	else if(which==2){//inorder; Left->Root->Right
		scan(ptr->left,2,o);
		print(ptr,o);
		scan(ptr->right,2,o);
	}
	else if(which==3){//postorder; Left->Right->Root
		scan(ptr->left,3,o);
		scan(ptr->right,3,o);
		print(ptr,o);
	}
}
void BinarySearchTree::preorder(ostream &o){
	scan(root,1,o);
}
void BinarySearchTree::inorder(ostream &o){
	scan(root,2,o);
}
void BinarySearchTree::postorder(ostream &o){
	scan(root,3,o);
}
//returns the address of the string's parent and whether it's a right child or not
node *BinarySearchTree::parent(char *string,node *ptr, bool *isRight){
	if(ptr!=nullptr){
		int comparator=strcmp(string,ptr->data);
		if(comparator<0){//string<ptr->data
			if(ptr->left!=nullptr){
				if(strcmp(ptr->left->data,string)==0){
					*isRight=false;
					return ptr;
				}
				else
					return parent(string,ptr->left,isRight);
			}
		}
		else if(comparator>0){//string>ptr->data
			if(ptr->right!=nullptr){
				if(strcmp(ptr->right->data,string)==0){
					*isRight=true;
					return ptr;
				}
				else
					return parent(string,ptr->right,isRight);
			}
		}
	}
	return nullptr;//Basically if the tree is empty or the string is in the root
}
bool BinarySearchTree::remove(char *string){
	bool isright=false;
	node *deleting=search(string,root);
	node* prnt=parent(string,root,&isright);
	if(deleting==nullptr)//String can't be found inside the tree
		return false;
	else if(deleting->instances>1)//All extra instances should be deleted before it's the node's turn
		deleting->instances--;
	else if(deleting==root){//It is a special case because prnt==nullptr
		node *temp;
		//if one of its children has the correct node available, its easy
		if(root->left!=nullptr && root->left->right==nullptr){
			temp=root;
			root=root->left;
			root->right=temp->right;
			delete [] temp->data;
			delete temp;
		}
		else if(root->right!=nullptr && root->right->left==nullptr){
			temp=root;
			root=root->right;
			root->left=temp->left;
			delete [] temp->data;
			delete temp;
		}
		else{//if not, its immediate next in ascending order should become the new root
			//ie the MIN of its right subtree
			//(this could have been generalized for all cases but its slower so there's
			// no reason to do it if it's not required)
			temp=root;
			node *MIN=root->right;
			node *parentMIN=root;
			while(MIN->left!=nullptr){
				parentMIN=MIN;
				MIN=MIN->left;
			}
			//Make MIN's child it's parent's child (Note that by definition the MIN can have at most one (right) child)
			parentMIN->left=MIN->right;
			root=MIN;
			root->left=temp->left;
			root->right=temp->right;
			delete [] temp->data;
			delete temp;
		}
	}
	else{//Assume instances==1; being lower than that should be impossible so the node must be removed regardless
		if(deleting->left==nullptr && deleting->right==nullptr){//First case: Leaf
			delete deleting->left;
			delete deleting->right;
			delete [] deleting->data;
			delete deleting;
			if(isright)
				prnt->right=nullptr;
			else
				prnt->left=nullptr;
		}
		else if(deleting->left==nullptr && deleting->right!=nullptr){//Second case: Single child (right)
			delete deleting->left;
			delete [] deleting->data;
			if(isright)
				prnt->right=deleting->right;
			else
				prnt->left=deleting->right;
			delete deleting;
		}
		else if(deleting->left!=nullptr && deleting->right==nullptr){//Second case: Single child (left)
			delete deleting->right;
			delete [] deleting->data;
			if(isright)
				prnt->right=deleting->left;
			else
				prnt->left=deleting->left;
			delete deleting;
		}
		else{//Third case: Two children
			//Next in line to occupy the "deleting" node is it's immediate next in ascending order
			node *MIN=deleting->right;
			node *prntMIN=deleting;
			while(MIN->left!=nullptr){
				prntMIN=MIN;
				MIN=MIN->left;
			}
			if(MIN!=deleting->right){//There's a chance the MIN is the immediate right child - without this an infinite loop occurs
				//Make MIN's child it's parent's child
				prntMIN->left=MIN->right;
				//Make "deleting"'s children Min's children
				MIN->right=deleting->right;
			}
			MIN->left=deleting->left;
			//Attach MIN to parent
			if(isright)
				prnt->right=MIN;
			else
				prnt->left=MIN;
			delete [] deleting->data;
			delete deleting;	
		}
	}
	return true;
}