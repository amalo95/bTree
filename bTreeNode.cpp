/*
 * bTreeNode.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: agustin
 */

#include "bTreeNode.h"
//Constructor
bTreeNode::bTreeNode(int maxL,bool _leaf) {
	// TODO Auto-generated constructor stub
	//Sets variables according to bTree Rules.
	maxLinks = maxL;
	maxKeys = maxL - 1;
	minKeys = maxL/2;
	//Sets keyCount to zero.
	keyCount = 0;
	leaf = _leaf;

	keyV = new keyValue[maxKeys];
	links = new bTreeNode *[maxLinks];
}
//Destructor
bTreeNode::~bTreeNode() {
	// TODO Auto-generated destructor stub
	delete []keyV;
	delete []links;
}

//recursively traverses through the sub-tree at current node to print out toStr
void bTreeNode::traverse(string* result){
	int i;
	//If not a leaf, traverse through children before concatenating current node's keys.
	if(this->leaf == false){
		for(i = 0; i<keyCount;i++){
			links[i]->traverse(result);
			*result += keyV[i].k + "\n";
		}
	}
	//Traverses through last link, if not a leaf.
	if(this->leaf == false){
		links[i]->traverse(result);
	}
	//If it is a leaf, iterate and concatenate.
	if(this->leaf){
		for(int j = 0; j<keyCount;j++){
			*result += keyV[j].k + "\n";
		}
	}

}

//Helper method to bTree:find(), adjusted the value of 'value' if it finds
bool bTreeNode::searchForKey(string key, string *value){

	//Iterate to find the first key >= to key
	int i = 0;
	while (i < keyCount && key > keyV[i].k)
		i++;

	//First if statement prevents, array index out of bounds
	if(i!=keyCount){
		//if key is found, it updates value of "value", exits by return.
		if (keyV[i].k == key){
			*value = keyV[i].v;
			return true;
		}
	}
	// If this is a leaf node, return false, searchForKey unsuccessful.
	if (leaf == true){

		return false;
	}
	// Clearly not a leaf, recursively go to next link.
	return links[i]->searchForKey(key,value);
}

//handles splitting nodes when the node is full (keyCount is at max)
void bTreeNode::split(int i,bTreeNode* lNode){

	// Initializes rightNode that is going to store, maxKeys/2 keys of left node.
	bTreeNode *rNode = new bTreeNode(lNode->maxLinks, lNode->leaf);
	rNode->keyCount = maxKeys/2;

	// Copy the last maxKeys/2 keys from lNode to new rNode.
	for (int j = 0; j < rNode->keyCount; j++){
		rNode->keyV[j] = lNode->keyV[j+maxKeys-rNode->keyCount];

	}
	// Copy the last minKey links from lNode to new rNode.
	if (lNode->leaf == false)
	{
		for (int j = 0; j < maxKeys; j++){
			rNode->links[j] = lNode->links[j+minKeys];
		}
	}

	// Adjust keyCount in lNode, from the keys that were transfered over.
	lNode->keyCount = maxKeys - rNode->keyCount -1;

	//Move over keys to make room for root node insertion.
	for (int j = keyCount; j >= i+1; j--){
		links[j+1] = links[j];
	}
	// Make rNode a link in root
	links[i+1] = rNode;

	// Middle element of lNode will go to root, move over keys in root.
	for (int j = keyCount-1; j >= i; j--){
		keyV[j+1] = keyV[j];
	}
	// Insert middle element of lNode to root.
	keyV[i] = lNode->keyV[lNode->keyCount];

	// Adjust the keyCount in root.
	keyCount++;

}

//Helper method to insert, specifically when the node hasn't reached its maxKeys limit.
void bTreeNode::insertNonFull(string key, string value){
	//Create keyValue pair "item" from given key and value strings.
	keyValue item;
	item.k = key;
	item.v = value;

	//Set i to last element:
	int i = keyCount -1;
	//If it is a leaf, make room for new key-value pair.
	if(leaf){
		while (i >= 0 && keyV[i].k > key)
		{
			keyV[i+1] = keyV[i];
			i--;
		}

		// Insert keyvalue pair in right spot.
		keyV[i+1] = item;

		//Adjust keyCount
		keyCount++;
	}
	else{
		//If its NOT a leaf, then we need to go to the correct leaf node so we can insert to a leaf.
		while (i >= 0 && keyV[i].k > key){
			i--;
		}
		//If link is full, split is required
		if (links[i+1]->keyCount == maxKeys)
		{
			split(i+1, links[i+1]);
			if (keyV[i+1].k < key){
				i++;
			}
		}
		//If link is NOT full, just insert it recursively.
		links[i+1]->insertNonFull(key,value);
	}
}


//Returns the index of first key in Node that is <= to k
int bTreeNode::findIndex(string k)
{
	int idex = 0;
	while (idex < keyCount && k > keyV[idex].k){
		++idex;
	}
	return idex;
}

// Helper method to delete_key, removes the key from tree,
// Recursively finding the right node and removing it with the appropriate helper method
void bTreeNode::remove(string k)
{
	int index = findIndex(k);

	//Remove from this node
	if (index < keyCount && keyV[index].k == k)
	{

		//Use correct helper method accordingly
		if (leaf){
			removeFromLeaf(index);
		}
		else{
			removeFromNonLeaf(index);
		}
	}
	else{

		// If node is a leaf, its not in Btree and return and do nothing.
		if (leaf)
		{
			//cout << "test: KEY NOT FOUND" << endl;
			return;
		}

		// flag variable tells us whether ket is present in last child.
		bool flag;
		if(index==keyCount){
			flag = true;
		}
		else{
			flag = false;
		}

		// If link has less that minKeys keys, fill link.
		if (links[index]->keyCount < minKeys){
			fill(index);
		}

		//If the last link was merged, we remove from correct link
		if (flag && index > keyCount){
			links[index-1]->remove(k);
		}else{
			links[index]->remove(k);
		}
	}
}

// Helper method that removes key from a lead node
void bTreeNode::removeFromLeaf (int index)
{
	// Move all the keys over to right place, deleting key at "index"
	for (int i=index+1; i<keyCount; ++i){
		keyV[i-1] = keyV[i];
	}

	// Adjust keyCount.
	keyCount--;
}

// Helper method that removes key from a non-lead node
void bTreeNode::removeFromNonLeaf(int index)
{
	string key = keyV[index].k;

	if (links[index]->keyCount >= minKeys)
	{
		// If link that precedes key has at least minkeys, we find the pred and recursively remove key from that node
		bTreeNode::keyValue pred = getPred(index);
		keyV[index] = pred;
		links[index]->remove(pred.k);
	}
	else if  (links[index+1]->keyCount >= minKeys)
	{
		// If link that succeeds key has at least minkeys, we find the succ and recursively remove key from that node
		bTreeNode::keyValue succ = getSucc(index);
		keyV[index] = succ;
		links[index+1]->remove(succ.k);
	}
	else
	{
		//If two links have less than minKets, merge them
		merge(index);
		links[index]->remove(key);
	}
}

// Helper method that returns the predecessor of the link at specified index
bTreeNode::keyValue bTreeNode::getPred(int index)
{
	// Find the right most node thats a leaf
	bTreeNode *current=links[index];

	while (!current->leaf){
		current = current->links[current->keyCount];
	}

	// Return the last key-value of node
	return current->keyV[current->keyCount-1];
}

// Helper method that returns the successor of the link at specified index
bTreeNode::keyValue bTreeNode::getSucc(int index)
{
	// Find the right most node thats a leaf
	bTreeNode *current = links[index+1];

	while (!current->leaf){
		current = current->links[0];
	}

	// Return the first key-value of node
	return current->keyV[0];
}

// Helper method that fills up the child node present in the index in the links array
void bTreeNode::fill(int index)
{
	// If the previous link has more than minKeys-1 keys, borrow a key from that child
	if (index != 0 && links[index-1]->keyCount >= minKeys){
		borrowFromLast(index);
	}
	else if (index!=keyCount && links[index+1]->keyCount>=minKeys){
		// If the next link has more than minKeys-1 keys, borrow a key from that child
		borrowFromNext(index);
	}
	else
	{
		//merge link with right sibling, unless its the most right one, merge with left
		if (index != keyCount){
			merge(index);
		}else{
			merge(index-1);
		}
	}
}

// Helper method that borrows a key from the links[index-1] node and replaces it in links[index]
void bTreeNode::borrowFromLast(int index)
{
	bTreeNode *child=links[index];
	bTreeNode *sibling=links[index-1];

	// Moving all keys in link one index ahead
	for (int i=child->keyCount-1; i>=0; --i){
		child->keyV[i+1] = child->keyV[i];
	}
	// If link is not a leaf, move all its child pointers one index ahead
	if (!child->leaf)
	{
		for(int i=child->keyCount; i>=0; --i){
			child->links[i+1] = child->links[i];
		}
	}

	// Setting child's first key-value pair equal to keyV[index-1] from the current node
	child->keyV[0] = keyV[index-1];

	// Moving sibling's last child as link's first child
	if (!leaf){
		child->links[0] = sibling->links[sibling->keyCount];
	}

	// Moving the keyValue from the sibling to the parent
	keyV[index-1] = sibling->keyV[sibling->keyCount-1];

	// Adjust keyCounts
	child->keyCount++;
	sibling->keyCount--;
}

// Helper method that borrows a key from the links[index+1] node and replaces it in links[index]
void bTreeNode::borrowFromNext(int index)
{
	bTreeNode *child=links[index];
	bTreeNode *sibling=links[index+1];

	// keyV[index] is inserted as the last keyvalue pair in links[index]
	child->keyV[(child->keyCount)] = keyV[index];

	// Sibling's first link is inserted as the last link
	// into links[index]
	if (!(child->leaf)){
		child->links[(child->keyCount)+1] = sibling->links[0];
	}
	//The first key from sibling is inserted into keys[index]
	keyV[index] = sibling->keyV[0];

	// Move all key values in sibling one index back
	for (int i=1; i<sibling->keyCount; ++i){
		sibling->keyV[i-1] = sibling->keyV[i];
	}
	// Move the links one index back
	if (!sibling->leaf)
	{
		for(int i=1; i<=sibling->keyCount; ++i){
			sibling->links[i-1] = sibling->links[i];
		}
	}

	// Adjust keyCounts
	child->keyCount++;
	sibling->keyCount--;
}

// A function to merge C[index] with C[index+1]
// C[index+1] is freed after merging
void bTreeNode::merge(int index)
{
	bTreeNode *child = links[index];
	bTreeNode *sibling = links[index+1];

	// taking away key-value pair from the current node and inserting it in link
	child->keyV[minKeys-1] = keyV[index];

	// Copying the keys from node to node.
	for (int i = 0; i < sibling->keyCount; ++i)
		child->keyV[i+minKeys] = sibling->keyV[i];

	// Copying the link pointers to node from node to node.
	if (!child->leaf)
	{
		for(int i = 0; i <= sibling->keyCount; ++i){
			child->links[i+minKeys] = sibling->links[i];
		}
	}

	//Move all keyvalue pairs to one index back to fill empty space.
	for (int i = index+1; i < keyCount; ++i){
		keyV[i-1] = keyV[i];
	}
	// Moving the child pointers after (index+1) in the current node one
	// step before
	for (int i=index+2; i<=keyCount; ++i){
		links[i-1] = links[i];
	}
	// Updating the key count of child and the current node
	child->keyCount += sibling->keyCount+1;
	keyCount--;

	// Free memory of sibling
	delete(sibling);
}


