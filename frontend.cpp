#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream> //needed for my to_string implementation
#include <climits>

using namespace std;

//TO DO
//possible 64-bit value support?

extern string toString(int input);
extern const string error;
extern string parseInt(string input);
extern string parseHex(string input);
extern string parseBin(string input);
extern string Bin_to_Int(string binary);
extern string Hex_to_Bin(string hexadecimal);
extern string Int_to_Hex(string integer);

void printResults(string integer, string hexadecimal, string binary);

int main() {
	
	string integer; //string for integer value
	string hexadecimal; //string for hexadecimal value
	string binary; //string for binary value
	string input; //string for user input
		
	while(true) {
		//resets variables
		integer = "";
		hexadecimal = "";
		binary = "";
		input = "";

		//prompt for input
		cout << "Enter a value. If the value is hexadecimal, prepend it with \"0x\". "
			 << "If the value is binary, prepend it with \"_\". "
			 << "Press q to quit.\n";
		getline(cin, input);

		//parses quit option
		if (input == "q" || input == "Q") return 1;
		
		//integer parsing, if input is integer begins cycle
		integer = parseInt(input);
		if (integer != error) {
			hexadecimal = Int_to_Hex(integer);
			binary = Hex_to_Bin(hexadecimal);
			printResults(integer, hexadecimal, binary);
			continue;
		}
		
		//hexadecimal parsing, if input is hexadecimal begins cycle
		hexadecimal = parseHex(input);
		if (hexadecimal != error) {
			binary = Hex_to_Bin(hexadecimal);
			integer = Bin_to_Int(binary);
			printResults(integer, hexadecimal, binary);
			continue;
		}
		
		//binary parsing, if input is binary begins cycle
		binary = parseBin(input);
		if (binary != error) {
			integer = Bin_to_Int(binary);
			hexadecimal = Int_to_Hex(integer);
			printResults(integer, hexadecimal, binary);
			continue;
		}
		
		//if no parsing works print error message
		cout << "INPUT ERROR\n";
		
	}
	return 0;
}

//prints results and ends chain of functions
void printResults(string integer, string hexadecimal, string binary) {
	cout << "Integer: " << integer << endl;
	cout << "Hexadecimal: " << hexadecimal << endl;
	cout << "Binary: " << binary << endl;
}
