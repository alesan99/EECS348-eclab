// Alejandro Sandoval
// EECS 348 Extra Credit Lab

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

const double INVALID_NUMBER = -999999.99;
const int MAX_LENGTH = 20;

double extractNumeric(const string& str);

int main() {
	string input;

	while (true) {
		cout << "Enter a string (or 'END' to quit): ";
		cin >> input;

		// End program
		if (input == "END") {
			break;
		}

		double number = extractNumeric(input);

		if (number != INVALID_NUMBER) {
			cout << "The input is: " << fixed << setprecision(4) << number << endl;
		} else {
			cout << "The input is invalid." << endl;
		}
	}

	return 0;
}

double extractNumeric(const string& str) {
	// Cannot be longer than 20 characters
	if (str.length() > MAX_LENGTH || str.length() == 0) {
		return INVALID_NUMBER;
	}

	double number = 0;

	bool decimal = false; // has decimal?
	double decimalPlace = 0.1; // where to place digit when decimal is true

	bool negative = false; // turn negative at the end
	bool hasNumber = false; // must contain number

	// Go through each character
	for (int i = 0; i < str.length(); i++) {
		char c = str[i];

		if (c >= '0' && c <= '9') { // compare ASCII values
			hasNumber = true; // string contains a number

			int digit = c - '0'; // subtract ASCII value of 0 to get the digit

			if (decimal) {
				number += digit * decimalPlace;
                decimalPlace *= 0.1; // move decimal place for next digit
			} else {
				number = number * 10 + digit;
			}
		} else if (c == '.') {
			// Can only have one decimal point
			if (decimal) {
				return INVALID_NUMBER;
			}
			decimal = true;
		} else if (c == '-') {
			// - must be the first character
			if (i != 0) {
				return INVALID_NUMBER;
			}
			negative = true;
		} else if (c == '+') {
			// + must be the first character
			if (i != 0) {
				return INVALID_NUMBER;
			}
		} else {
			return INVALID_NUMBER;
		}
	}

	// String must contain at least 1 number
	if (!hasNumber) {
		return INVALID_NUMBER;
	}

	// Turn negative
	if (negative) {
		number *= -1;
	}

	return number;
}