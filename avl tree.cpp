#include <bits/stdc++.h>
using namespace std;

struct Node{
	int value; // এখানে ভ্যালু রাখা হবে 
	Node *left_node=NULL; // বামের নোড রাখা হবে এখানে 
	Node *right_node=NULL; // ডানের নোড রাখা হবে এখানে 
	int height=0; //আমাদের ট্রি এর উচ্চতা এখানে জমা রাখা হবে
};

int height(Node *node){
	if(node==NULL){
		return -1;
	}else{
		return node->height;
	}
}


Node *right_rotate(Node *node){
	Node *temp=node;
	node=temp->left_node;
				
	temp->left_node=node->right_node; //যদি কেন্দ্রীয় নোডের কোন ডান সাবট্রি থাকে তবে তা উপরের প্রান্তীয় নোডের বাম সাবট্রি হিসেবে থাকবে
	temp->height=max(height(temp->left_node),height(temp->right_node))+1; //পুনরায় প্রান্তীয় নোডের উচ্চতা সেট করতে হবে
				
	node->right_node=temp; //কেন্দ্রীয় নোডের ডান সাব-ট্রি হিসেবে temp ট্রি টি যুক্ত করি
	node->height=max(height(node->left_node),height(node->right_node))+1; //পুনরায় কেন্দ্রীয় নোডের উচ্চতা হিসাব করি। 
	return node;
}

Node *left_rotate(Node *node){
	Node *temp=node;
	node=temp->right_node;
				
	temp->right_node=node->left_node; //যদি কেন্দ্রীয় নোডের কোন ডান সাবট্রি থাকে তবে তা উপরের প্রান্তীয় নোডের বাম সাবট্রি হিসেবে থাকবে
	temp->height=max(height(temp->left_node),height(temp->right_node))+1; //পুনরায় প্রান্তীয় নোডের উচ্চতা সেট করতে হবে
				
	node->left_node=temp; //কেন্দ্রীয় নোডের ডান সাব-ট্রি হিসেবে temp ট্রি টি যুক্ত করি
	node->height=max(height(node->left_node),height(node->right_node))+1; //পুনরায় কেন্দ্রীয় নোডের উচ্চতা হিসাব করি। 
	return node;
}


Node *left_right_rotate(Node *node){
	
	Node *temp=node->left_node; //নোড ২
	node->left_node=temp->right_node; //২ নং নোড এর জায়গায় ৩ নং নোডকে দিলাম			
	temp->right_node=node->left_node->left_node; //২ নং নোডের ডান সাবট্রি হিসেবে ৩ নং নোডের বাম সাবট্রিকে দিলাম
	node->left_node->left_node=temp; // ২ নং নোডকে ৩ নং নোডের বাম সাবট্রি হিসেবে সংযুক্ত করলাম
	//উচ্চতা আপডেট করা হবে এখন 
	int node_2_height=max(height(node->left_node->left_node->left_node),height(node->left_node->left_node->right_node))+1;
	node->left_node->left_node->height=node_2_height;
	
	int node_3_height=max(height(node->left_node->right_node),height(node->left_node->left_node))+1;
	node->left_node->height=node_3_height;
	
	node=right_rotate(node); //নোডকে ডানে ঘুরালাম। 
	return node;
}

Node *right_left_rotate(Node *node){
	Node *temp=node->right_node; //নোড ২
	node->right_node=temp->left_node; //২ নং নোড এর জায়গায় ৩ নং নোডকে দিলাম			
	temp->left_node=node->right_node->right_node; //২ নং নোডের ডান সাবট্রি হিসেবে ৩ নং নোডের বাম সাবট্রিকে দিলাম
	node->right_node->right_node=temp; // ২ নং নোডকে ৩ নং নোডের বাম সাবট্রি হিসেবে সংযুক্ত করলাম
	//উচ্চতা আপডেট করা হবে এখন 
	int node_2_height=max(height(node->right_node->right_node->left_node),height(node->right_node->right_node->right_node))+1;
	node->right_node->right_node->height=node_2_height;
	
	int node_3_height=max(height(node->right_node->right_node),height(node->right_node->left_node))+1;
	node->right_node->height=node_3_height;
	
	node=left_rotate(node); //নোডকে বামে ঘুরালাম। 
	return node;
}

Node *insert(int num,Node *node){
	cout<<"Visiting "<<(node==NULL?num:node->value)<<endl;
	if(node==NULL){ //node==null হলে আমরা বুঝতে পারবো আমরা বাম, ডান করতে করতে সবার শেষে পৌঁছেছি। রুট নোডের ক্ষেত্রেও এই শর্ত সত্য
		Node *temp=new Node(); // নতুন একটা নোড তৈরি করি
		temp->value=num;
		temp->height=0;
		return temp;
	}else if(num<=node->value){
		//আমরা বামে যাবো, কারণ আমাদের num এর মান বর্তমান নোডের থেকে কম 
		node->left_node=insert(num,node->left_node);
	}else{
		//আমরা ডানে যাবো, কারণ আমাদের num এর মান বর্তমান নোডের থেকে বেশি 
		node->right_node=insert(num,node->right_node);
	}
	
	//বর্তমান নোড (node) এর ডান এবং বাম সাব-ট্রি এর মধ্যে যার উচ্চতা সব থেকে বেশি, আমাদের বর্তমান নোডের উচ্চতা হবে তার থেকে ১ বেশি। 
	node->height=max(height(node->left_node),height(node->right_node))+1;
	
	
	//সকল রিকার্সিভ হিসাব নিকাশের পরে এখানে আসবে, এখুন আমরা যে সাব-ট্রি তে আছি তার সকল নোডের উচ্চিতা জানি।
	//তাই আমরা ব্যালেন্স ফ্যাক্টর হিসাব করতে পারবো। 
	int bf=height(node->left_node)-height(node->right_node);
	
	//এখন যদি ব্যালেন্স ফ্যাক্টর {-1,0,1} এর বাইরে কিছু হয় তার মানে হলো আনাদের ট্রি/সাবট্রি টি ব্যালেন্স না, তাই আমাদের ব্যালেন্স করে নিতে হবে।
	if(bf>1){
		if(node->left_node->value<num){ // তারমানে Left-Right ভারসাম্যহীনতা
			node=left_right_rotate(node);
		}else{ // অথবা Left-Left ভারসাম্যহীনতা
			node=right_rotate(node);
		}
	}else if(bf<-1){
		if(node->right_node->value>num){// তারমানে num Right Left ভারসাম্যহীনতা
			node=right_left_rotate(node);
		}else{//অথবা Right-Right ভারসাম্যহীনতা
			node=left_rotate(node);
		}
	}
	
	return node;
}


int main(){
	Node *root=NULL;
	root=insert(100,root);
	cout<<"---------------\n";
	root=insert(50,root);
	cout<<"---------------\n";
	root=insert(30,root);
	cout<<"---------------\n";
	root=insert(150,root);
	cout<<"---------------\n";
	root=insert(180,root);
	cout<<"---------------\n";
	root=insert(200,root);
	cout<<"---------------\n";
	root=insert(20,root);
	cout<<"---------------\n";
	root=insert(25,root);
	cout<<"---------------\n";
	root=insert(27,root);
	cout<<"---------------\n";
	root=insert(125,root);
	cout<<"---------------\n";
	root=insert(40,root);
	cout<<"---------------\n";
	root=insert(115,root);
}
