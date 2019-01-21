#pragma once

/******************************************************************
Program Name: List.h

Des: This class is used to create a linked list of strings. Data
	can be inserted, deleted, or edited in the list. The data can
	also be printed out.

Author: Matthew Day

Due Date: 10/15/18
*******************************************************************/

#include <iostream>
#include <string>

using namespace std;

struct Node {

	string data;
	Node *prev;
	Node *next;
};

class List {

private:

	Node *head;
public:

	/******************************************************************
	Name: List

	Des:
		Constructor creates an empty linked list.
	*******************************************************************/
	List();

	/******************************************************************
	Name: ~List

	Des:
		Destructor deletes the list from the heap
	*******************************************************************/
	~List();

	/******************************************************************
	Name: Insert

	Des:
		Inserts data into the list in ascending order and returns true
		if successful.

	Params:
		data - type string, the data to inserted into the list.

	Return:
		type boolean, true if successful and false if the memory
		allocation fails.
	*******************************************************************/
	bool Insert(string data);

	/******************************************************************
	Name: Delete

	Des:
		Deletes data from the list.

	Params:
		data - type string, the data to deleted from the list.

	Return:
		type boolean, true if successful and false if the data couldn
		not be found in the list.
	*******************************************************************/
	bool Delete(string data);

	/******************************************************************
	Name: Edit

	Des:
		Deletes the previous data from the list and inserts new data
		in ascending order.

	Params:
		previousData - type string, the existing value to be edited.
		newData - type string, the new value to be added.

	Return:
		type boolean, true if successful otherwise false.
	*******************************************************************/
	bool Edit(string previousData, string newData);

	/******************************************************************
	Name: Print

	Des:
		Prints all data in the list to the console
	*******************************************************************/
	void Print();
private:

	/******************************************************************
	Name: insertFront

	Des:
		Inserts the node into the front of the list

	Params:
		cur - type Node pointer, the node to be inserted.
	*******************************************************************/
	void insertFront(Node *cur);

	/******************************************************************
	Name: insertBack

	Des:
		Inserts the node into the back of the list

	Params:
		lastNode - type Node pointer, the node that is at the back
			of the list.
		cur - type Node pointer, the node to be inserted.
	*******************************************************************/
	void insertBack(Node *lastNode, Node *cur);

	/******************************************************************
	Name: insertMiddle

	Des:
		Inserts the node in the middle of the list

	Params:
		lastNode - type Node pointer, the node that the new node is to
			be inserted after.
		cur - type Node pointer, the node to be inserted.
	*******************************************************************/
	void insertMiddle(Node *lastNode, Node *cur);

	/******************************************************************
	Name: deleteFront

	Des:
		Deletes the node from the front of the list
	*******************************************************************/
	void deleteFront();

	/******************************************************************
	Name: deleteBack

	Des:
		Deletes the node from the back of the list
	Params:
		cur - type Node pointer, the node to be deleted.
	*******************************************************************/
	void deleteBack(Node *cur);

	/******************************************************************
	Name: deleteMiddle

	Des:
		Deletes the node from the middle of the list

	Params:
		cur - type Node pointer, the node to be deleted.
	*******************************************************************/
	void deleteMiddle(Node *cur);
};