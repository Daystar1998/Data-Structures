/******************************************************************
Program Name: baseConverter.cpp

Des: This program will input a list of decimals and bases from the
	file "numbers.txt" and convert the decimals to the bases.

Author: Matthew Day

Due Date: 9/10/18
*******************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

/******************************************************************
Function Name: convertToHex

Des: This function converts the number to hexidecimal and returns it

Parameters: n - contains the number that needs to be converted
*******************************************************************/

char convertToHex(int n) {

	switch (n) {

		case 10:

			return 'A';
		case 11:

			return 'B';
		case 12:

			return 'C';
		case 13:

			return 'D';
		case 14:

			return 'E';
		case 15:

			return 'F';
		default:

			return 48 + n; // Add 48 to get the ASCII code for the number
	};
}

/******************************************************************
Function Name: converter

Des: This function converts the decimal to the base and prints the result.

Parameters: decimal - contains the decimal number.
			base - contains the base number.
*******************************************************************/

void converter(int decimal, int base) {

	if (decimal < base) {

		cout << convertToHex(decimal);
		return;
	} else {

		int decDivBase = decimal / base;

		converter(decDivBase, base);

		cout << convertToHex(decimal % base);
	}
}

/******************************************************************
Function Name: parseFile

Des: This function loads the file and parses for the decimal and
	base. It checks that the decimal is valid and returns if it
	is negative. Otherwise, it converts the decimal to the base.

Parameters: filename - Name of the file to be opened
*******************************************************************/

void parseFile(char *filename) {

	ifstream f(filename);
	string line;

	if (!f.is_open()) {

		cout << "Error: Couldn't open file " << filename << endl;
		return;
	}

	while (getline(f, line)) {

		stringstream stream(line);

		int decimal, base;

		stream >> decimal;
		stream >> base;

		if (decimal > 1000000000) {

			cout << "Decimal number too large for this program" << endl;
			continue;
		} else if (decimal < 0)
			return;

		converter(decimal, base);

		cout << endl;
	}
}

/******************************************************************
MAIN PROGRAM
*******************************************************************/

void main() {

	parseFile("res/numbers.txt");
	system("PAUSE");
}