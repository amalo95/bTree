/*
 * bTree.h
 *
 *  Created on: Apr 15, 2015
 *      Author: agustin
 */

#include <iostream>
#include <string>
#include "bTreeNode.h"

using namespace std;

#ifndef BTREE_H_
#define BTREE_H_

class bTree {
private:
	//Variable that holds the root Node of B-Tree
	bTreeNode* root;
	//Holds the maximum number of links a node in the bTree can have, specified by the user
	int maxLinks;
public:
	//Constructor
	bTree(int maxL);

	//Destructor
	~bTree();

	//Inserts the value pair into the tree
	bool insert(string key, string value);

	// Searches for the key in the tree, if found, it returns
	// true else returns false.
	// If the key is found, it stores the value in the *value variable
	bool find(string key, string *value);

	//Searches for the key and deletes it. Returns true if deletion was
	//successful, returns false if the key wasn't found
	bool delete_key(string key);

	// concatenates the contents of the tree from an inorder traversal
	// into an output stream with each string item followed by a
	// newline character in the stream
	string toStr();

	//helper method for toStr that will traverse root node.
	void traverse(string* result);
};

#endif /* BTREE_H_ */
