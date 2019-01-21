/******************************************************************
File Name: bst.cpp

Des: This file implements bst.h.

Author: Matthew Day

Due Date: 12/6/18
*******************************************************************/

#include "bst.h"

BST::BST() : root(nullptr) {}

BST::~BST() {

	deleteTree(root);
	root = nullptr;
}

bool BST::BSTadd(BSTtype &info) {

	bool result = false;

	Node *current = new Node();

	// Ensure memory was allocated
	if (current != nullptr) {

		// Set the node's key
		strcpy_s(current->info, info);

		// Set the node's frequency
		current->frequency = 1;

		result = insertNode(root, current);
		nodeCount++;
	}

	return result;
}

bool BST::BSTdelete(BSTtype &info) {

	bool result = false;

	if (root != nullptr) {

		Node *current = root;

		while (current != nullptr) {

			int comparison = strcmp(info, current->info);

			// Current node
			if (comparison == 0) {

				break;
			// Node to the left
			} else if (comparison < 0) {

				current = current->left;
			// Node to the right
			} else {

				current = current->right;
			}
		}

		// If info was found
		if (current != nullptr) {

			Node *parent = current->parent;

			// Delete leaf node
			if (isLeafNode(current)) {

				deleteLeafNode(current);
			// Delete two child node
			} else if (isTwoChildNode(current)) {

				deleteTwoChildNode(current);
			// Delete one child node
			} else {

				deleteOneChildNode(current);
			}

			// Update the height for each node that needs it
			while (parent != nullptr && setNodeHeight(parent)) {

				// Re-balance the tree
				balance(parent);
				parent = parent->parent;
			}

			// Only decrease the node count when something is actually deleted
			nodeCount--;
			result = true;
		}
	}

	return result;
}

bool BST::BSTexists(BSTtype &info) {

	bool result = false;

	Node *current = root;

	while (current != nullptr) {

		// Compare the cstrings only once
		int compareInfo = strcmp(info, current->info);

		// If found
		if (compareInfo == 0) {

			result = true;
			break;
		// Info is less than the current value
		} else if (compareInfo < 0) {

			current = current->left;
		// Info is greater than the current value
		} else {

			current = current->right;
		}
	}

	return result;
}

bool BST::BSTinc(BSTtype &info) {

	bool result = false;

	Node *current = root;

	while (current != nullptr) {

		// Compare the cstrings only once
		int compareInfo = strcmp(info, current->info);

		// If found
		if (compareInfo == 0) {

			current->frequency++;
			result = true;
			break;
		// Info is less than the current value
		} else if (compareInfo < 0) {

			current = current->left;
		// Info is greater than the current value
		} else {

			current = current->right;
		}
	}

	return result;
}

void BST::BSTprint(char letter, ostream &outStream) {

	printTree(root, letter, outStream);
}

void BST::BSTprint(ostream &outStream) {

	printTree(root, outStream);
}

int BST::getBSTNodeCount() {

	return nodeCount;
}

int BST::getBSTHeight() {

	int result = 0;

	if (root != nullptr)
		result = root->height;

	return result;
}

void BST::deleteTree(Node *current) {

	if (current != nullptr) {

		// Post-order traversal/deletion
		deleteTree(current->left);
		deleteTree(current->right);
		delete current;
	}
}

bool BST::insertNode(Node *parent, Node *current) {

	bool result = false;

	// Root is null
	if (root == nullptr) {

		root = current;
		current->parent = nullptr;
		result = true;
	} else {

		Node *nextParent = nullptr;
		Node *nextCurrent = parent;

		// If nextCurrent is null then we have found our insertion point
		while (nextCurrent != nullptr) {

			// Left of nextCurrent 
			if (strcmp(current->info, nextCurrent->info) <= 0) {

				nextParent = nextCurrent;
				nextCurrent = nextCurrent->left;
			// Right of nextCurrent
			} else {

				nextParent = nextCurrent;
				nextCurrent = nextCurrent->right;
			}
		}

		// Insert to left of parent
		if (strcmp(current->info, nextParent->info) <= 0) {

			nextParent->left = current;
		// Insert to right of parent
		} else {

			nextParent->right = current;
		}

		// Set parent
		current->parent = nextParent;

		// Update the height for each node that needs it
		while (current->parent != nullptr && setNodeHeight(current->parent)) {

			current = current->parent;

			// Ensure the tree is balanced 
			balance(current);
		}

		result = true;
	}

	return result;
}

void BST::deleteLeafNode(Node *current) {

	// Remove the current node from the tree

	Node *parent = current->parent;

	// Current is root
	if (parent == nullptr) {

		root = nullptr;
	// Current is left of parent
	} else if (current == parent->left) {

		parent->left = nullptr;
	// Current is right of parent
	} else if (current == parent->right) {

		parent->right = nullptr;
	}

	// Delete current
	delete current;
}

void BST::deleteOneChildNode(Node *current) {

	Node *child;

	// If the child node is the left node
	if (current->left != nullptr) {

		child = current->left;
	// If the child node is the right node
	} else {

		child = current->right;
	}

	// Remove the current node from the tree and replace with its child

	Node *parent = current->parent;

	// Current is root
	if (parent == nullptr) {

		root = child;
	// Current is left of parent
	} else if (parent->left == current) {

		parent->left = child;
	// Current is right of parent
	} else {

		parent->right = child;
	}

	child->parent = parent;

	// Delete current
	delete current;
}

void BST::deleteTwoChildNode(Node *current) {

	// This function should only be called when current->left is not null
	Node *nextCurrent = current->left;

	// Loop to find the leaf node closest to the current node
	while (nextCurrent->right != nullptr) {

		nextCurrent = nextCurrent->right;
	}

	// Copy the node
	strcpy_s(current->info, nextCurrent->info);
	current->frequency = nextCurrent->frequency;

	// Get the parent
	Node *nextParent = nextCurrent->parent;

	// Delete the copied node

	// Leaf node
	if (isLeafNode(nextCurrent)) {

		deleteLeafNode(nextCurrent);
	// One child node
	} else {

		deleteOneChildNode(nextCurrent);
	}

	// Update the height and re-balance for each node that needs it
	while (nextParent != nullptr && setNodeHeight(nextParent)) {

		balance(nextParent);
		nextParent = nextParent->parent;
	}

	// Ensure current's height was reset and is balanced
	setNodeHeight(current);
	balance(current);
}

bool BST::isLeafNode(Node *current) {

	// Are both of the children null
	return current->left == nullptr && current->right == nullptr;
}

bool BST::isTwoChildNode(Node *current) {

	// Are neither of the children null
	return current->left != nullptr && current->right != nullptr;
}

void BST::printTree(Node *current, char letter, ostream &outStream) {

	if (current != nullptr) {

		// Words starting with the letter are to the left
		if (letter < current->info[0]) {

			printTree(current->left, letter, outStream);
		// Words starting with the letter are to the right
		} else if (letter > current->info[0]) {

			printTree(current->right, letter, outStream);
		// The word in the current node starts with the letter
		} else {

			// In-order print
			printTree(current->left, letter, outStream);
			outStream << current->info << endl;
			printTree(current->right, letter, outStream);
		}
	}
}

void BST::printTree(Node *current, ostream &outStream) {

	if (current != nullptr) {

		// In-order print
		printTree(current->left, outStream);
		outStream << left << setw(20) << current->info << current->frequency << endl;
		printTree(current->right, outStream);
	}
}

bool BST::setNodeHeight(Node *current) {

	bool result = false;

	int leftHeight = 0;
	int rightHeight = 0;

	// Height of the left branch
	if (current->left != nullptr)
		leftHeight = current->left->height;

	// Height of the right branch
	if (current->right != nullptr)
		rightHeight = current->right->height;

	// The left branch height is longest and different from the current height
	if (leftHeight >= rightHeight && current->height != leftHeight + 1) {

		current->height = leftHeight + 1;
		result = true;
	// The right branch height is longest and different from the current height
	} else if (rightHeight >= leftHeight && current->height != rightHeight + 1) {

		current->height = rightHeight + 1;
		result = true;
	}

	return result;
}

void BST::balance(Node *current) {

	int leftHeight = 0;
	int rightHeight = 0;

	if (current->left != nullptr)
		leftHeight = current->left->height;

	if (current->right != nullptr)
		rightHeight = current->right->height;

	// Balance off to the left
	if (leftHeight > rightHeight + 1) {

		// Rotate right when the left branch leans left
		if (current->left->right == nullptr || (current->left->left != nullptr && current->left->right->height <= current->left->left->height)) {

			rotationRR(current);
		// Rotate left then right when the left branch leans right
		} else {

			rotationLR(current);
		}
	// Balance off to the right
	} else if (rightHeight > leftHeight + 1) {

		// Rotate left when the right branch leans right
		if (current->right->left == nullptr || (current->right->right != nullptr && current->right->left->height <= current->right->right->height)) {

			rotationLL(current);
		// Rotate right then left when the right branch leans left
		} else {

			rotationRL(current);
		}
	}

	// If the balance is not off then just exit the function
}

void BST::rotationLL(Node *current) {

	Node *parent = current->parent;

	Node *tmp = current->right;

	// Current is root
	if (parent == nullptr) {

		root = tmp;
	// Current is right of parent
	} else if (parent->right == current) {

		parent->right = tmp;
	// Current is left of parent
	} else {

		parent->left = tmp;
	}

	tmp->parent = parent;

	// Take the branch on tmp's left and connect it to current's right
	current->right = tmp->left;

	if(current->right != nullptr)
		current->right->parent = current;

	// Connect current to tmp's left
	tmp->left = current;
	current->parent = tmp;

	// Reset current's height
	setNodeHeight(current);

	// Reset tmp's height
	setNodeHeight(tmp);
}

void BST::rotationLR(Node *current) {

	Node *child = current->left;

	// Rotate the left sub-branch to the left
	rotationLL(child);

	// Rotate the current branch to the right
	rotationRR(current);
}

void BST::rotationRR(Node *current) {

	Node *parent = current->parent;

	Node *tmp = current->left;

	// Current is root
	if (parent == nullptr) {

		root = tmp;
	// Current is right of parent
	} else if (parent->right == current) {

		parent->right = tmp;
	// Current is left of parent
	} else {

		parent->left = tmp;
	}

	tmp->parent = parent;

	// Take the branch on tmp's right and connect it to current's left
	current->left = tmp->right;

	if (current->left != nullptr)
		current->left->parent = current;

	// Connect current to tmp's right
	tmp->right = current;
	current->parent = tmp;

	// Reset current's height
	setNodeHeight(current);

	// Reset tmp's height
	setNodeHeight(tmp);
}

void BST::rotationRL(Node *current) {

	Node *child = current->right;

	// Rotate the right sub-branch to the right
	rotationRR(child);

	// Rotate the current branch to the left
	rotationLL(current);
}