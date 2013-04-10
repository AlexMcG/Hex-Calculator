#include <iostream>
//#include <string> //might need this for windows
#include <cstdlib>
#include <cmath>

#include <sstream> //needed for my to_string

using namespace std;

//TO DO
//try and keep it to 32 bit SIGNED values DONE
//try to handle negative values

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
		//integer, hexadecimal, binary, input = "";
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



//g++ and clang do not support c++11 to_string. had to roll my own.
string to_string(int input) {
	stringstream output;
	output << input;
	return output.str();
}

bool parseInt() {
	cout << "parse int\n";

	//formatting check
	if (input.length() == 0) return false;
	if (to_string(atoi(input.c_str())).compare(input) != 0) return false; //returns false if over INT_MAX constant.
	unsigned int count = 0;
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
	cout << "parse hex\n";

	//formatting check
	if ((10 < input.length()) || (input.length() < 3)) return false;
	if ((input[0] != '0') || (input[1] != 'x')) return false;
	unsigned int count = 2;
	string allowed = "1234567890ABCDEF";
	while (count < input.length()) {
		input[count] = (char) toupper(input[count]); //may have to be changed to string
		if (input.npos == allowed.find(input[count])) return false;
		count++;
	}

	//if formatted right sets hexadecimal string and moves on
	hexadecimal = input;
	Hex_to_Bin();
	return true;
}

bool parseBin() {
	cout << "parse bin\n";

	//formatting check
	if ((33 < input.length()) || (input.length() < 2)) return false;
	unsigned int count = 1;
	if (input[0] != '_') return false;
	while (count < input.length()) {
		if ((input[count] != '0') && (input[count] != '1')) return false;
		count++;
	}

	//if formatted right, sets binary string and moves on
	input.replace(0, 1, ""); //deletes underscore so it can be stored correctly
	binary = input;
	Bin_to_Int();
	return true;
}


void Int_to_Hex() {
	cout << "int to hex\n";
	//checks completion
	if (hexadecimal == "") {
		//conversion
		int realint = atoi(integer.c_str());
		string *remainders = new string[9];
		int count = 0;
		if (!realint) remainders[count] = "0";
		while (realint) {
			remainders[count] = to_string(realint % 16);
			realint /= 16;
			count++;
		}

		int newcount = 0;
		hexadecimal += "0x";
		while (newcount <= count) {
			if (remainders[count] == "10") remainders[count] = "A";
			else if (remainders[count] == "11") remainders[count] = "B";
			else if (remainders[count] == "12") remainders[count] = "C";
			else if (remainders[count] == "13") remainders[count] = "D";
			else if (remainders[count] == "14") remainders[count] = "E";
			else if (remainders[count] == "15") remainders[count] = "F";
			hexadecimal += remainders[count]; 
			count--;
		}
		Hex_to_Bin();
	} else printResults();  //if done prints results
}


void Hex_to_Bin() {
	cout << "hex to bin\n";
	//checks completion
	if (binary == "") {
		//conversion
		unsigned int count = 2;
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


void Bin_to_Int() {
	cout << "bin to int\n";
	//checks completion
	if (integer == "") {
		//conversion
		int realint = 0;
		unsigned int count = 0;
		int length = binary.length() - 1;
		while (0 <= length) {
			if (binary[length] == '1') realint += int(pow(2, count));
			count++;
			length--;
		}
		integer = to_string(realint);
		Int_to_Hex();
	} else printResults();  //if done prints results
}

//prints results and ends chain of functions
void printResults() {
	cout << "Integer: " << integer << endl;
	cout << "Hexadecimal: " << hexadecimal << endl;
	cout << "Binary: " << binary << endl;
}
