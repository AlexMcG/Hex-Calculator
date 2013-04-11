#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream> //needed for my to_string implementation
#include <climits>

using namespace std;

//TO DO
//possible 64-bit value support?

string integer; //string for integer value
string hexadecimal; //string for hexadecimal value
string binary; //string for binary value
string input; //string for user input

bool parseInt();
bool parseHex();
bool parseBin();
void Bin_to_Int();
void Hex_to_Bin();
void Int_to_Hex();
void printResults();

int main() {	
	while(true) {
		//resets global variables
		integer = "";
		hexadecimal = "";
		binary = "";
		input = "";

		//prompt for input
		cout << "Enter a value. If the value is hexadecimal, prepend it with \"0x\". "
			 << "If the value is binary, prepend it with \"_\". "
			 << "Press q to quit.\n";
		getline(cin, input);

		//parses input
		if (input == "q" || input == "Q") return 1; //quit option
		if (!(parseInt() || parseHex() || parseBin())) cout << "INPUT ERROR\n";
	}
	return 0;
}



//ubuntu 13.04 libs do not support c++11 to_string. had to roll my own.
string toString(int input) {
	stringstream output;
	output << input;
	return output.str();
}

bool parseInt() {
	//cout << "parse int\n"; //debug

	//formatting check
	if (input.length() == 0) return false;
	if (toString(atoi(input.c_str())).compare(input) != 0) return false; //returns false if over INT_MAX.
	int count = 0;
	if (input[0] == '-') count++; //for negative values
	while (count < input.length()) {
		if (!isdigit(input[count])) return false;
		count++;
	}

	//if formatted right sets integer string moves on
	integer = input;
	Int_to_Hex();
	return true;
}

bool parseHex() {
	//cout << "parse hex\n"; //debug

	//formatting check
	if ((10 < input.length()) || (input.length() < 3)) return false;
	if ((input[0] != '0') || (input[1] != 'x')) return false;
	int count = 2;
	string allowed = "1234567890ABCDEF";
	while (count < input.length()) {
		input[count] = (char) toupper(input[count]);
		if (input.npos == allowed.find(input[count])) return false;
		count++;
	}
	
	//formats with leading zeroes
	input.erase(0, 2);
	while (input.length() < 8) {
			input.insert(0, "0");
	}
	input.insert(0, "0x");
	
	//if formatted right sets hexadecimal string and moves on
	hexadecimal = input;
	Hex_to_Bin();
	return true;
}

bool parseBin() {
	//cout << "parse bin\n"; //debug

	//formatting check
	if ((33 < input.length()) || (input.length() < 2)) return false;
	int count = 1;
	if (input[0] != '_') return false;
	while (count < input.length()) {
		if ((input[count] != '0') && (input[count] != '1')) return false;
		count++;
	}

	//formats with leading zeroes and removes "_" for storage
	input.erase(0, 1);
	while (input.length() < 32) {
			input.insert(0, "0");
	}
	
	//if formatted right, sets binary string and moves on
	binary = input;
	Bin_to_Int();
	return true;
}


void Int_to_Hex() {
	//cout << "int to hex\n"; //debug

	//checks completion
	if (hexadecimal == "") {
		//conversion
		int realint = atoi(integer.c_str());
		int remainders[8];

		if (realint < 0) {
			fill_n(remainders, 8, 15);
			realint++;
		} else fill_n(remainders, 8, 0);
				
		int count = 0;
		while (realint) {
			remainders[count] += realint % 16;
			realint /= 16;
			count++;
		}
				
		hexadecimal += "0x";
		count = 7;
		while (count >= 0) {
			if (remainders[count] == 10) hexadecimal += "A";
			else if (remainders[count] == 11) hexadecimal += "B";
			else if (remainders[count] == 12) hexadecimal += "C";
			else if (remainders[count] == 13) hexadecimal += "D";
			else if (remainders[count] == 14) hexadecimal += "E";
			else if (remainders[count] == 15) hexadecimal += "F";
			else hexadecimal += toString(abs(remainders[count]));
			count--;
		}
		Hex_to_Bin();
	} else printResults();  //if done prints results
}


void Hex_to_Bin() {
	//cout << "hex to bin\n"; //debug

	//checks completion
	if (binary == "") {
		//conversion
		int count = 2;
		char hexSymbols[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		while (count < hexadecimal.length()) {
			if (hexadecimal[count] == hexSymbols[0]) binary += "0000";
			else if (hexadecimal[count] == hexSymbols[1]) binary += "0001";
			else if (hexadecimal[count] == hexSymbols[2]) binary += "0010";
			else if (hexadecimal[count] == hexSymbols[3]) binary += "0011";
			else if (hexadecimal[count] == hexSymbols[4]) binary += "0100";
			else if (hexadecimal[count] == hexSymbols[5]) binary += "0101";
			else if (hexadecimal[count] == hexSymbols[6]) binary += "0110";
			else if (hexadecimal[count] == hexSymbols[7]) binary += "0111";
			else if (hexadecimal[count] == hexSymbols[8]) binary += "1000";
			else if (hexadecimal[count] == hexSymbols[9]) binary += "1001";
			else if (hexadecimal[count] == hexSymbols[10]) binary += "1010";
			else if (hexadecimal[count] == hexSymbols[11]) binary += "1011";
			else if (hexadecimal[count] == hexSymbols[12]) binary += "1100";
			else if (hexadecimal[count] == hexSymbols[13]) binary += "1101";
			else if (hexadecimal[count] == hexSymbols[14]) binary += "1110";
			else if (hexadecimal[count] == hexSymbols[15]) binary += "1111";
			count++;
		}
		Bin_to_Int();
	} else printResults();  //if done prints results
}

float two = 2; //set to float so compiler will use the right function in windows
void Bin_to_Int() {
	//cout << "bin to int\n"; //debug
	
	//checks completion
	if (integer == "") {
		//conversion
		int realint = 0;
		int count = 0;
		int length = binary.length() - 1;
		while (0 <= length) {
			if (binary[length] == '1') realint += int(pow(two, count));
			count++;
			length--;
		}
		integer = toString(realint);
		Int_to_Hex();
	} else printResults();  //if done prints results
}

//prints results and ends chain of functions
void printResults() {
	cout << "Integer: " << integer << endl;
	cout << "Hexadecimal: " << hexadecimal << endl;
	cout << "Binary: " << binary << endl;
}
