#include <cstdlib>
#include <cmath>
#include <sstream> //needed for my to_string implementation

using namespace std;

//parsing error string
const string error = "";

//ubuntu 13.04 libs do not support c++11 to_string. had to roll my own.
string toString(int input) {
	stringstream output;
	output << input;
	return output.str();
}

string parseInt(string input) {
	//cout << "parse int\n"; //debug

	//formatting check
	if (input.length() == 0) return error;
	if (toString(atoi(input.c_str())).compare(input) != 0) return error; //returns error if over INT_MAX.
	unsigned int count = 0;
	if (input[0] == '-') count++; //for negative values
	while (count < input.length()) {
		if (!isdigit(input[count])) return error;
		count++;
	}

	//if formatted right returns input
	return input;
}

string parseHex(string input) {
	//cout << "parse hex\n"; //debug
	
	//formatting check
	if ((10 < input.length()) || (input.length() < 3)) return error;
	if ((input[0] != '0') || (input[1] != 'x')) return error;
	unsigned int count = 2;
	string allowed = "1234567890ABCDEF";
	while (count < input.length()) {
		input[count] = (char) toupper(input[count]);
		if (input.npos == allowed.find(input[count])) return error;
		count++;
	}
	
	//formats with leading zeroes
	input.erase(0, 2);
	while (input.length() < 8) {
			input.insert(0, "0");
	}
	input.insert(0, "0x");
	
	//if formatted right returns input
	return input;
}

string parseBin(string input) {
	//cout << "parse bin\n"; //debug

	//formatting check
	if ((33 < input.length()) || (input.length() < 2)) return error;
	unsigned int count = 1;
	if (input[0] != '_') return error;
	while (count < input.length()) {
		if ((input[count] != '0') && (input[count] != '1')) return error;
		count++;
	}

	//formats with leading zeroes and removes "_" for storage
	input.erase(0, 1);
	while (input.length() < 32) {
			input.insert(0, "0");
	}
	
	//if formatted right returns input
	return input;
}


string Int_to_Hex(string integer) {
	//cout << "int to hex\n"; //debug

	//output 
	string hexadecimal = "";
	
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
	return hexadecimal;
}


string Hex_to_Bin(string hexadecimal) {
	//cout << "hex to bin\n"; //debug
	
	//output
	string binary = "";
	
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
	return binary;
}

float two = 2; //set to float so compiler will use the right function in windows
string Bin_to_Int(string binary) {
	//cout << "bin to int\n"; //debug
	
	//output
	string integer = "";
	
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
	return integer;
}
