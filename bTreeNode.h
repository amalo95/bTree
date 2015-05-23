/*
 * BTreeNode.h
 *
 *  Created on: Apr 15, 2015
 *      Author: agustin
 */

#include <string>
#include <iostream>

using namespace std;

#ifndef BTREENODE_H_
#define BTREENODE_H_

class bTreeNode {
	//struct that holds the key-value pair of strings:
	typedef struct keyValue {
		string k;
		string v;
	} keyValue;

	//holds an array of keyValue pairs
	keyValue *keyV;

	//holds an array of pointers to bTreeNodes
	bTreeNode** links;

	//holds the maximum number of links to other nodes
	int maxLinks;

	//holds the minimum number of keys
	int minKeys;

	//holds the maximum number of keys
	int maxKeys;

	//holds the number of keys a specific node has
	int keyCount;

	//Holds the truth value of a node, true if leaf, false if not a leaf.
	bool leaf;

public:
	//Constructor
	bTreeNode(int maxL, bool leaf);

	//Destructor
	virtual ~bTreeNode();

	//recursively traverses through the sub-tree at current node to print out toStr
	void traverse(string* result);

	//Helper method to bTree:find(), adjusted the value of 'value' if it finds
	bool searchForKey(string key, string *value);

	//handles splitting nodes when the node is full (keyCount is at max)
	void split(int i,bTreeNode* rNode);

	//Helper method to insert, specifically when the node hasn't reached its maxKeys limit.
	void insertNonFull(string key, string value);

	/*--------------------------DELETING NODES HELPER METHODS:--------------------------*/

	//Returns the index of first key in Node that is >= to k
	int findIndex(string k);

	// Helper method to delete_key, removes the key from tree,
	//rescursively finding the right node and removing it with the appropriate helper method
	void remove(string k);

	// Helper method that removes key from a lead node
	void removeFromLeaf(int idex);

	// Helper method that removes key from a non-lead node
	void removeFromNonLeaf(int idex);

	// Helper method that returns the predecessor of the link at specified index
	keyValue getPred(int idex);

	// Helper method that returns the successor of the link at specified index
	keyValue getSucc(int idex);

	// Helper method that fills up the child node present in the index in the links array
	void fill(int idex);

	// Helper method that borrows a key from the links[index-1] node and replaces it in links[index]
	void borrowFromLast(int idex);

	// Helper method that borrows a key from the links[index+1] node and replaces it in links[index]
	void borrowFromNext(int idex);

	//Helper method that merges two nodes
	void merge(int idex);

	//Allows bTree to use "keyValue" pairs
	friend class bTree;


};

#endif /* BTREENODE_H_ */
