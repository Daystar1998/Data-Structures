#pragma once

/******************************************************************
File Name: stack.h

Class Name: Stack

Des: This class is used to create a stack of coordinates.

Author: Matthew Day

Due Date: 11/7/18
*******************************************************************/

class Stack {

public:

	struct Coordinate {

		int row, column;

		/******************************************************************
		Struct Constructor
		******************************************************************/
		Coordinate(int row, int column)
			: row(row), column(column) {
		}
	};

private:

	struct Node {

		Coordinate location;
		Node *next;

		/******************************************************************
		Struct Constructor
		******************************************************************/
		Node(Coordinate location) : location(location){}
	};

	// Top of the stack
	Node *top;
public:

	/******************************************************************
	Class Constructor
	******************************************************************/
	Stack();

	/******************************************************************
	Class Destructor
	******************************************************************/
	~Stack();

	/******************************************************************
	Function Name: push

	Des:
		Pushs a Coordinate onto the top of the stack.

	Params:
		location - type Coordinate &, the coordinate to be pushed on
			the stack

	Returns:
		type bool, true if successful, otherwise false
	******************************************************************/
	bool push(Coordinate &location);

	/******************************************************************
	Function Name: pop

	Des:
		Pops a Coordinate off the top of the stack.

	Params:
		location - type Coordinate &, output of the coordinate to be
			popped off the top of the stack

	Returns:
		type bool, true if successful, otherwise false
	******************************************************************/
	bool pop(Coordinate &location);

	/******************************************************************
	Function Name: empty

	Des:
		Checks if the stack is empty.

	Returns:
		type bool, true if empty, otherwise false
	******************************************************************/
	bool empty();

	/******************************************************************
	Function Name: peak

	Des:
		Pops a Coordinate off the top of the stack.

	Params:
		location - type Coordinate &, output of the coordinate on top
			of the stack.
	******************************************************************/
	void peak(Coordinate &location);
};

