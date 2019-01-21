#pragma once

/******************************************************************
File Name: bst.h

Class Name: BST

Des: This class is used to create a binary tree structure.

Author: Matthew Day

Due Date: 12/6/18
*******************************************************************/

#include <cstring>
#include <iostream>
#include <iomanip>

using std::ostream;
using std::endl;
using std::setw;
using std::left;

const int MAX_LENGTH = 30;

typedef char BSTtype[MAX_LENGTH];

class BST {

private:

	struct Node {

		BSTtype info;
		int frequency;
		int height = 1;

		Node *parent;
		Node *left = nullptr;
		Node *right = nullptr;
	};
private:

	Node *root;
	int nodeCount;
public:

	/******************************************************************
		Class Constructor
	******************************************************************/
	BST();

	/******************************************************************
		Class Destructor
	******************************************************************/
	~BST();

	/******************************************************************************
		Function Name: BSTadd
		
		Des:
			Adds info to the tree
			
		Params:
			info - type BSTtype &, the data to be added
			
		Returns:
			type bool, true if successful, otherwise false
	******************************************************************************/
	bool BSTadd(BSTtype &info);

	/******************************************************************************
		Function Name: BSTdelete

		Des:
			Deletes info from the tree

		Params:
			info - type BSTtype &, the data to be deleted

		Returns:
			type bool, true if successful, otherwise false
	******************************************************************************/
	bool BSTdelete(BSTtype &info);

	/******************************************************************************
		Function Name: BSTexists

		Des:
			Check if the info is in the tree

		Params:
			info - type BSTtype &, the data to be searched for

		Returns:
			type bool, true if it exists, otherwise false
	******************************************************************************/
	bool BSTexists(BSTtype &info);

	/******************************************************************************
		Function Name: BSTinc

		Des:
			Increment the frequency of the data

		Params:
			info - type BSTtype &, the data whose frequency is to be incremented

		Returns:
			type bool, true if it exists, otherwise false
	******************************************************************************/
	bool BSTinc(BSTtype &info);

	/******************************************************************************
		Function Name: BSTprint
		
		Des:
			Prints all words that begin with the specified letter
			
		Params:
			letter - type char, the letter showing which words should be printed
			outStream - type ostream &, the output stream to be printed to
	******************************************************************************/
	void BSTprint(char letter, ostream &outStream);

	/******************************************************************************
		Function Name: BSTprint

		Des:
			Prints all words in the tree along with their frequency

		Params:
			outStream - type ostream &, the output stream to be printed to
	******************************************************************************/
	void BSTprint(ostream &outStream);

	/******************************************************************************
		Function Name: getBSTNodeCount

		Des:
			Get the number of nodes in the tree

		Returns:
			type int, the number of nodes in the tree
	******************************************************************************/
	int getBSTNodeCount();

	/******************************************************************************
		Function Name: getBSTHeight
		
		Des:
			Get the height of the tree
			
		Returns:
			type int, the height of the tree
	******************************************************************************/
	int getBSTHeight();

private:

	/******************************************************************************
		Function Name: deleteTree
		
		Des:
			Deletes every node in the tree
			
		Params:
			current - type Node *, the current node to be deleted
	******************************************************************************/
	void deleteTree(Node *insertNode);

	/******************************************************************************
		Function Name: insertNode

		Des:
			Insert a node into the tree

		Params:
			parent - type Node *, the parent of the tree
			current - type Node *, the current node to be inserted

		Returns:
			type bool, true if successful, otherwise false
	******************************************************************************/
	bool insertNode(Node *parent, Node *current);

	/******************************************************************************
		Function Name: deleteLeafNode

		Des:
			Deletes a node which is a leaf

		Params:
			current - type Node *, the current node to be deleted
	******************************************************************************/
	void deleteLeafNode(Node *current);

	/******************************************************************************
		Function Name: deleteOneChildNode

		Des:
			Deletes a node which has one child

		Params:
			current - type Node *, the current node to be deleted

		Returns:
			type bool, true if successful, otherwise false
	******************************************************************************/
	void deleteOneChildNode(Node *current);

	/******************************************************************************
		Function Name: deleteTwoChildNode
		
		Des:
			Deletes a node which has two children
			
		Params:
			current - type Node *, the current node to be deleted
	******************************************************************************/
	void deleteTwoChildNode(Node *current);

	/******************************************************************************
		Function Name: isLeafNode

		Des:
			Checks if the current node is a leaf

		Params:
			current - type Node *, the current node to be checked

		Returns:
			type bool, true if it is a leaf, otherwise false
	******************************************************************************/
	bool isLeafNode(Node *current);

	/******************************************************************************
		Function Name: isTwoChildNode
		
		Des:
			Checks if the current node has two child nodes
			
		Params:
			current - type Node *, the current node to be checked
			
		Returns:
			type bool, true if it has two children, otherwise false
	******************************************************************************/
	bool isTwoChildNode(Node *current);

	/******************************************************************************
		Function Name: printTree

		Des:
			Prints all words in the tree that start with the specified letter

		Params:
			current - type Node *, the current node
			letter - type char, the letter showing which words should be printed
			outStream - type ostream &, the output stream to be printed to
	******************************************************************************/
	void printTree(Node *current, char letter, ostream &outStream);

	/******************************************************************************
		Function Name: printTree

		Des:
			Prints all words in the tree along with their frequency

		Params:
			current - type Node *, the current node
			outStream - type ostream &, the output stream to be printed to
	******************************************************************************/
	void printTree(Node *current, ostream &outStream);

	/******************************************************************************
		Function Name: setNodeHeight
		
		Des:
			Set's the height of the node to the longest branch
			
		Params:
			current - type Node *, the node who's height is to be set
			
		Returns:
			type bool, true if the height is changed, otherwise false
	******************************************************************************/
	bool setNodeHeight(Node *current);

	/******************************************************************************
		Function Name: balance
		
		Des:
			Balances the tree
			
		Params:
			current - type Node *, the node which needs to be re-balanced
	******************************************************************************/
	void balance(Node *current);

	/******************************************************************************
		Function Name: rotationLL
		
		Des:
			Rotates the off-balance branch to the left
			
		Params:
			current - type Node *, the node which needs to be re-balanced
	******************************************************************************/
	void rotationLL(Node *current);

	/******************************************************************************
		Function Name: rotationLR

		Des:
			Rotates the off-balance branch's sub-branch to the left then rotate
				the branch to the right

		Params:
			current - type Node *, the node which needs to be re-balanced
	******************************************************************************/
	void rotationLR(Node *current);

	/******************************************************************************
		Function Name: rotationRR

		Des:
			Rotates the off-balance branch to the right

		Params:
			current - type Node *, the node which needs to be re-balanced
	******************************************************************************/
	void rotationRR(Node *current);

	/******************************************************************************
		Function Name: rotationRL

		Des:
			Rotates the off-balance branch's sub-branch to the right then rotate
				the branch to the left

		Params:
			current - type Node *, the node which needs to be re-balanced
	******************************************************************************/
	void rotationRL(Node *current);
};