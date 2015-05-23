/*
 * bTree.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: agustin
 */

#include "bTree.h"


//Constructor
bTree::bTree(int maxL){
	maxLinks = maxL;
	root = NULL;
}

//Destructor
bTree::~bTree(){}

//Inserts the value pair into the tree
bool bTree::insert(string key, string value){
	//Creates the "item" to insert
	bTreeNode::keyValue item;
	item.k = key;
	item.v = value;

	//This will happen when the first key is inserted for the first time
	if(this->root == NULL){
		this->root = new bTreeNode(maxLinks, true);
		this->root->keyV[0] = item;

		this->root->keyCount = 1;
	}
	else{
		//When the keyCount is at its max, a split must occur first before inserting
		if(root->keyCount == root->maxKeys){
			bTreeNode* newRoot = new bTreeNode(maxLinks,false);

			newRoot->links[0] = root;

			newRoot->split(0,root);

			int i = 0;
			if (newRoot->keyV[0].k < key)
				i++;
			newRoot->links[i]->insertNonFull(key,value);

			// Change root
			root = newRoot;


		}else{
			//Since keyCount is not at its max we can just insert using the following method
			root->insertNonFull(key,value);
		}
	}
	return 0;
}

// Searches for the key in the tree, if found, it returns
// true else returns false.
// If the key is found, it stores the value in the *value variable
bool bTree::find(string key, string *value){
	bool there= false;
	if(root!=NULL){
		if(root->searchForKey(key,value)){
			there = true;
		}
	}
	return there;
}

//Searches for the key and deletes it. Returns true if deletion was
//successful, returns false if the key wasn't found
bool bTree::delete_key(string key){
	if (!root) {
		return false;
	}

	root->remove(key);

	if (root->keyCount == 0) {
		bTreeNode *temp = root;
		if (root->leaf) {
			root= NULL;
		}
		else{
			root = root->links[0];
		}
		delete temp;
	}
	return true;
}

// concatenates the contents of the tree from an inorder traversal
// into an output stream with each string item followed by a
// newline character in the stream
string bTree::toStr(){
	string result;

	traverse(&result);

	return result;
}

//helper method for toStr that will traverse root node.
void bTree::traverse(string *result){

	if(root==NULL){
	}
	else{
		//Will traverse node if its not empty
		root->traverse(result);
	}
}
