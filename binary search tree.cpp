/*
Sharif Hasan - CSE, PUST
site: https://iishanto.com
*/
#include<bits/stdc++.h>

using namespace std;


struct Node{
	int value;
	Node *left_node=NULL;
	Node *right_node=NULL;
};


Node *insert(int num,Node *node){
	if(node==NULL){
		Node *temp=new Node();
		temp->value=num;
		return temp;
	}else if(num<=node->value){
		node->left_node=insert(num,node->left_node);
	}else{
		node->right_node=insert(num,node->right_node);
	}
	return node;
}


Node *search(int num,Node *node){
	if(node==NULL) return NULL;
	if(node->value==num){
		return node;
	}else if(num<=node->value){
		return search(num,node->left_node);
	}else{
		return search(num,node->right_node);
	}
}


int find_minimum(Node *node){
	if(node==NULL) return false;
	if(node->left_node==NULL){
		return node->value;
	}
	return find_minimum(node->left_node);
}


Node *delete_node(int num,Node *node){
	if(node==NULL) return NULL;
	if(num<node->value){
		node->left_node = delete_node(num,node->left_node);
	}else if(num>node->value){
		node->right_node = delete_node(num,node->right_node);
	}
	else{
		if(node->left_node==NULL&&node->right_node==NULL){
			delete []node;
			node =NULL;
		}else if(node->left_node!=NULL&&node->right_node==NULL){
			Node *temp=node->left_node;
			delete []node;
			node=temp;
		}else if(node->right_node!=NULL&&node->left_node==NULL){
			Node *temp=node->right_node;
			delete []node;
			node=temp;
		}else{
			int val=find_minimum(node->right_node);
			node->value=val;
			node->right_node=delete_node(val,node->right_node);
		}
	}
	return node;
}

int main(){
	Node *tree_root=NULL;
	tree_root=insert(5,tree_root);
	insert(7,tree_root);
	insert(6,tree_root);
	insert(3,tree_root);
	insert(0,tree_root);
	
	tree_root=delete_node(3,tree_root); //delete node 3
	if(search(3,tree_root)!=NULL){
		cout<<"3 কে পেয়েছি\n";
	}else{
		cout<<"3 কে পাই নি, দুঃখিত\n";
	}return 0;
}
