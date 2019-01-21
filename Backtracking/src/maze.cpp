/******************************************************************
File Name: maze.cpp

Des:
	This program loads a maze from a file and attempts find an
		exit. It then prints the maze with breadcrumbs and whether
		or not it was able to find the exit to a file.

Author: Matthew Day

Due Date: 11/11/18
*******************************************************************/

#include <fstream>

#include "stack.h"

using std::ifstream;
using std::ofstream;
using std::endl;

struct LocationType {

	const char PATH = '0';
	const char HEDGE = '1';
	const char EXIT = 'E';
	const char BREADCRUMB = 46;
};

/******************************************************************
Function Name: readMaze

Des:
	Reads the maze and the starting position from the file.

Params:
	fin - type ifstream &, the input file to be read from
	maze - type char [][80], output for the maze layout
	numRows - type int &, output the number of rows in the
		maze
	numColumns - type int &, output the number of columns in the
		maze
	startRow - type int &, output the row to start searching
		from
	startColumn - type int &, output the column to start searching
		from

Returns:
	type bool, false if numRows or numCols equals -1, otherwise
		true
******************************************************************/
bool readMaze(ifstream &fin, char maze[][80], int &numRows, int &numColumns, int &startRow, int &startColumn) {

	bool result = true;

	// Get the dimensions of the current maze
	fin >> numRows;
	fin >> numColumns;

	if (numRows == -1 || numColumns == -1)
		result = false;
	else {

		// Loops through the rows
		for (int r = 0; r < numRows; r++) {

			// Loops through the columns
			for (int c = 0; c < numColumns; c++) {

				// Fills the maze with data from the file
				fin >> maze[r][c];
			}
		}

		// Get the start position
		fin >> startRow;
		fin >> startColumn;
	}

	return result;
}

/******************************************************************
Function Name: printMaze

Des:
	Writes the output of the maze to the file

Params:
	fout - type ofstream &, the input file to be written to
	maze - type char [][80], the maze layout
	numRows - type int, the number of rows in the maze
	numColumns - type int, the number of columns in the maze
	currentMaze - type int, number of the current maze to be
		printed
	exitFound - type bool, an exit was found for the current
		maze
******************************************************************/
void printMaze(ofstream &fout, char maze[][80], int numRows, int numColumns, int currentMaze, bool exitFound) {

	// Print the number of the current maze with a new line before and after it
	fout << "\nMAZE NUMBER " << currentMaze << "\n" << endl;

	// Loops through the rows
	for (int r = 0; r < numRows; r++) {

		// Loops through the columns
		for (int c = 0; c < numColumns; c++) {

			// Wirtes the maze's data to the file
			fout << maze[r][c];
		}

		// Start the next row on a new line
		fout << endl;
	}

	// Check if an exit was found
	if (exitFound) {

		// Print exit found
		fout << "\nThere IS a way out" << endl;
	} else {

		// Print exit not found
		fout << "\nThere IS NOT a way out" << endl;
	}
}

/******************************************************************
Function Name: processCoordinate

Des:
	Process the coordinate to see if it is inside the maze, and is
		the exit, or a valid move.

Params:
	maze - type char [][80], the maze layout
	numRows - type int, the number of rows in the maze
	numColumns - type int, the number of columns in the maze
	row - type int, the row for the current coordinate
	column - type int, the column for the current coordinate
	availableMoves - type Stack &, the list of all available moves
Returns:
	type bool, true if exit, otherwise false
******************************************************************/
bool processCoordinate(char maze[][80], int numRows, int numColumns, int row, int column, Stack &availableMoves) {

	bool exitFound = false;

	// Check whether the coordinate is inside of the maze
	if (row >= 0 && column >= 0 && row < numRows && column < numColumns) {

		// Check if the coordinate is the exit
		if (maze[row][column] == 'E') {

			exitFound = true;
		} // Check if the coordinate is a valid path
		else if (maze[row][column] == '0') {

			// Add the coordinate to the stack of available moves
			Stack::Coordinate coordinate(row, column);
			availableMoves.push(coordinate);
		}
	}

	return exitFound;
}

/******************************************************************
Function Name: processMaze

Des:
	Process the maze to try to find an exit

Params:
	maze - type char [][80], the maze layout
	numRows - type int, the number of rows in the maze
	numColumns - type int, the number of columns in the maze
	start - type stack::Coordinate, the starting location
	exitFound - type bool &, output if an exit was found for the
		current maze
******************************************************************/
void processMaze(char maze[][80], int numRows, int numColumns, Stack::Coordinate start, bool &exitFound) {

	// Stack of all unprocessed path coordinates
	Stack availableMoves;

	// The coordinate currently being processed
	Stack::Coordinate current = start;

	// Initialize exitFound to false
	exitFound = false;

	// Check if the starting coordinate is the exit
	if (maze[current.row][current.column] == 'E') {

		exitFound = true;
	} else {

		// Push the starting coordinate onto the stack
		availableMoves.push(start);
	}

	// Loop until there are no more moves
	while (!availableMoves.empty()) {

		// Set the current coordinate to what's on top of the stack
		availableMoves.pop(current);

		// Drop breadcrumb on current coordinate
		maze[current.row][current.column] = '.';

		// Check east to see if it is the exit or a valid move. Exit breaks out of the loop, valid moves are added to the stack
		if (processCoordinate(maze, numRows, numColumns, current.row, current.column + 1, availableMoves)) {

			exitFound = true;
			break;
		}

		// Check west to see if it is the exit or a valid move. Exit breaks out of the loop, valid moves are added to the stack
		if (processCoordinate(maze, numRows, numColumns, current.row, current.column - 1, availableMoves)) {

			exitFound = true;
			break;
		}

		// Check north to see if it is the exit or a valid move. Exit breaks out of the loop, valid moves are added to the stack
		if (processCoordinate(maze, numRows, numColumns, current.row - 1, current.column, availableMoves)) {

			exitFound = true;
			break;
		}

		// Check south to see if it is the exit or a valid move. Exit breaks out of the loop, valid moves are added to the stack
		if (processCoordinate(maze, numRows, numColumns, current.row + 1, current.column, availableMoves)) {

			exitFound = true;
			break;
		}
	}
}

int main() {

	// Open the file maze.txt for input
	ifstream fin("res/maze.txt");

	// Open the file mazeSolutions.txt for output
	ofstream fout("res/mazeSolutions.txt");

	// Print title to the file
	fout << "Solutions to A-MAZE-ING Stacks Assignment" << endl;

	// Print my name to the
	fout << "Matthew Day" << endl;

	int numRows;
	int numColumns;
	int startRow;
	int startColumn;

	char maze[80][80];

	bool exitFound = false;
	int currentMaze = 1;

	// Read in and process maze's until the stop character is found
	while (readMaze(fin, maze, numRows, numColumns, startRow, startColumn)) {

		// Create starting coordinate
		Stack::Coordinate start(startRow, startColumn);

		// Attempts to find the exit to the maze
		processMaze(maze, numRows, numColumns, start, exitFound);

		// Prints the maze results to a file
		printMaze(fout, maze, numRows, numColumns, currentMaze, exitFound);

		currentMaze++;
	}
}