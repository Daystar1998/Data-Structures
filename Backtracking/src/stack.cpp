/******************************************************************
File Name: stack.cpp

Des: This file implements stack.h.

Author: Matthew Day

Due Date: 11/11/18
*******************************************************************/

#include "stack.h"

Stack::Stack() {

	// Initialize top to null;
	top = nullptr;
}

Stack::~Stack() {

	Node *tmp;

	// Loop through until nothing else is still in the stack
	while (!empty()) {

		// Safely delete the node from the heap without leaving any dangling pointers or memory leaks
		tmp = top;
		top = top->next;
		delete tmp;
	}
}

bool Stack::push(Coordinate &location) {

	// Create a node with the location to be pushed on the stack
	Node *node = new Node(location);
	bool result = false;

	// Checks whether memory was successfully allocated
	if (node != nullptr) {

		// Insert the new node onto the top of the stack
		node->next = top;
		top = node;

		result = true;
	}

	return result;
}

bool Stack::pop(Coordinate &location) {

	Node *tmp;
	bool result = false;

	// Checks if there is anything on the stack to pop off
	if (!empty()) {

		// Get the coordinate from the top of the stack
		location = top->location;

		// Safely delete the node from the heap without leaving any dangling pointers or memory leaks
		tmp = top->next;
		delete top;
		top = tmp;

		result = true;
	}

	return result;
}

bool Stack::empty() {

	return top == nullptr;
}

void Stack::peak(Coordinate &location) {

	// Get the coordinate from the top of the stack
	location = top->location;
}