#include "BinarySearchTreeAVL.h"

BinarySearchTreeAVL::BinarySearchTreeAVL():BinarySearchTree(){}
int BinarySearchTreeAVL::treeHeight(node *ptr){
	if(ptr==nullptr)
		return 0;
	int heightR=1+treeHeight(ptr->right);
	int heightL=1+treeHeight(ptr->left);
	return heightR>heightL ? heightR : heightL;
}
int BinarySearchTreeAVL::heightDiff(node* ptr){
	return treeHeight(ptr->left)-treeHeight(ptr->right);
}
void BinarySearchTreeAVL::leftRotation(node *ptr,node *prnt,bool isRight){
	node *temp=ptr->right;
	int hRtree=treeHeight(temp->right);
	int hLtree=treeHeight(temp->left);
	if(hLtree<=hRtree){//simple L rotation
		if(ptr==root)
			root=temp;
		else if(isRight)
			prnt->right=temp;
		else
			prnt->left=temp;
		ptr->right=temp->left;
		temp->left=ptr;
	}
	else{//RL rotation
		node *temp1=temp->left;
		if(ptr==root)
			root=temp1;
		else if(isRight)
			prnt->right=temp1;
		else
			prnt->left=temp1;
		ptr->right=temp1->left;
		temp->left=temp1->right;
		temp1->left=ptr;
		temp1->right=temp;
	}
}
void BinarySearchTreeAVL::rightRotation(node *ptr,node *prnt,bool isRight){
	node *temp=ptr->left;
	int hRtree=treeHeight(temp->right);
	int hLtree=treeHeight(temp->left);
	if(hRtree<=hLtree){//simple R rotation
		if(ptr==root)
			root=temp;
		else if(isRight)
			prnt->right=temp;
		else
			prnt->left=temp;
		ptr->left=temp->right;
		temp->right=ptr;
	}
	else{//LR rotation
		node *temp1=temp->right;
		if(ptr==root)
			root=temp1;
		else if(isRight)
			prnt->right=temp1;
		else
			prnt->left=temp1;
		temp->right=temp1->left;
		ptr->left=temp1->right;
		temp1->left=temp;
		temp1->right=ptr;
	}
}
bool BinarySearchTreeAVL::scanForUnbalance(node * ptr, node* prnt,bool isRight){
	if(ptr==nullptr)//Safeguard for crashes; if the tree is empty it cannot be unbalanced
		return false;
	int HD=heightDiff(ptr);
	bool resp3=false;
	if(HD!=0 && HD!=1 && HD!=-1){
		if(HD<-1)//Unbalanced right subtree
			leftRotation(ptr,prnt,isRight);
		else if(HD>1)//Unbalanced left subtree
			rightRotation(ptr,prnt,isRight);
		resp3=true;
	}
	bool resp1=scanForUnbalance(ptr->left,ptr,false);
	bool resp2=scanForUnbalance(ptr->right,ptr,true);
	//Return true if at least one change was made
	return (resp1 || resp2 || resp3);
}
void BinarySearchTreeAVL::insert(char *string){
	BinarySearchTree::insert(string);//add string
	node* prnt=nullptr;
	bool isright=false;
	scanForUnbalance(root,prnt,isright);
}
bool BinarySearchTreeAVL::remove(char *string){
	bool response=BinarySearchTree::remove(string);//delete string
	if(response){
		node* prnt=nullptr;
		bool isright=false;
		scanForUnbalance(root,prnt,isright);
	}
	return response;
}