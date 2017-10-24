/*
Compiling and Running cannibals.cpp: the only required file is cannibals.cpp. In Linux console, with the cannibals.cpp file in the correct directory, you need to enter the following: g++ cannibals.cpp
Once this compiles, enter the following to see the output: ./a.out
Libraries used in this program are the following:
<iostream>: required to output data to console
<string>: required to output strings to console
<queue>: required to use functionality of this data structure in the program
<stdlib.h>: required for functionality of the exit command when compiling in Linux
*/

#include <iostream>
#include <string>
#include <queue>
#include <stdlib.h>

using std::queue;
using namespace std;

//FORWARD DECLARATIONS
void loadBoat(int* people, queue<char>& boat, string l, string r);
queue<char> empty(queue<char>& boat);
string printState(int* people);
string printMidRiver(queue<char>& boat);
string printRightBank(int* people);
string printLeftBank(int* people);

//LOADBOAT
//Takes in an array of integers, a queue of chars that represent the boat, a string for the left bank
//output and a string for the right bank output. Contains the complete algorithm that the program 
//uses to decide which action to take depending on the current state of the program.
void loadBoat(int* people, queue<char>& boat, string l, string r) {

	string left = l;//current state of the left bank
	string right = r;//current state of the right bank

	//steps back in recursive stack if cannibals outnumber explorers on left bank
	if (people[2] > people[1] && people[1] != 0) {
		return;
	}
	//steps back in recursive stack if cannibals outnumber explorers on right bank
	else if (people[4] > people[3] && people[3] != 0) {
		return;
	}
	//steps back in recursive stack if the number of people would be reduced below 0 
	else if (people[1] < 0 || people[2] < 0 || people[3] < 0 || people[4] < 0) {
		return;
	}
	//state is allowed by criteria. outputs current state
	else if (people[0] > 0){
		if (people[0] % 2 != 0) {
			left = printLeftBank(people);
		}
		else {
			right = printRightBank(people);
		}
		string add = printMidRiver(boat);
		//outputs state with boat in transit
		cout << left << add << right << endl;
		left = printLeftBank(people);
		right = printRightBank(people);
		string next = printState(people);
		//outputs state once boat arrives to shore
		cout << left << next << right << endl;
	}
	//runs algorithm while base case has not been satisfied
	while (people[3] != 3 || people[4] != 3) {
		people[0]++;
		//possibles moves while boat is on left bank
		if (people[0] % 2 != 0) {
			//people[0]++;
			boat = empty(boat);
			people[2]-=2;
			people[4]+= 2;
			boat.push('C');
			boat.push('C');
			loadBoat(people, boat, left, right); //move 2 cannibals
			boat = empty(boat);
			people[1] -= 2;
			people[2] += 2;
			people[3] += 2;
			people[4] -= 2;
			boat.push('E');
			boat.push('E');
			loadBoat(people, boat, left, right); // move 2 explorers
			boat = empty(boat);
			people[1]++;
			people[2]--;
			people[3]--;
			people[4]++;
			boat.push('E');
			boat.push('C');
			loadBoat(people, boat, left, right);//move 1 explorer and 1 cannibal
		}
		//possible moves while boat is on right bank
		else if (people[0] % 2 == 0) {
			//people[0]++;
			boat = empty(boat);
			people[1]++;
			people[3]--;
			boat.push('-');
			boat.push('E');
			loadBoat(people, boat, left, right);//move 1 explorer
			boat = empty(boat);
			people[1]--;
			people[2]++;
			people[3]++;
			people[4]--;
			boat.push('-');
			boat.push('C');
			loadBoat(people, boat, left, right);//move 1 cannibal
			boat = empty(boat);
			people[1]++;
			people[3]--;
			boat.push('E');
			boat.push('C');
			loadBoat(people, boat, left, right);//move 1 explorer and 1 cannibal
		}
	}
	exit(0);
}

//EMPTY
//Takes in a queue<char>. Empties boat before testing each state of the algorithm
//returns a queue<char> that is an empty boat.
queue<char> empty(queue<char>& boat) {
	queue<char> out = boat;
	while (!out.empty()) {
		out.pop();
	}
	return out;
}

//PRINTSTATE
//Takes in an int*. Determines the current location of the empty boat and returns
//a string that represents the boat's position
string printState(int* people) {
	string out;
	if (people[0] % 2 == 0) {
		out += "\\--/        ";
	}
	else {
		out += "        \\--/";
	}
	return out;
}

//PRINTMIDRIVER
//Takes in a queue<char> that represents the full boat. Empties the boat
//into a string. Returns the string.
string printMidRiver(queue<char>& boat) {
	string out;
	out += "    \\";
	while (!boat.empty()) {
		out += boat.front();
		boat.pop();
	}
	out += "/    ";
	return out;
}

//PRINTLEFTBANK
//Takes in an int*. Parses the state of the left bank from ints to a string. Returns the string.
string printLeftBank(int* people) {
	string out;
	for (int i = 0; i < 3; i++) {
		if (people[1] - i <= 0) {
			out += "-";
		}
		else {
			out += "E";
		}
	}
	for (int j = 0; j < 3; j++) {
		if (people[2] - j <= 0) {
			out += "-";
		}
		else {
			out += "C";
		}
	}
	return out;
}

//PRINTRIGHTBANK
//Takes in an int*. Parses the state of the right bank from ints to a string. Returns the string.
string printRightBank(int* people) {
	string out;
	for (int i = 0; i < 3; i++) {
		if (people[3] - i <= 0) {
			out += "-";
		}
		else {
			out += "E";
		}
	}
	for (int j = 0; j < 3; j++) {
		if (people[4] - j <= 0) {
			out += "-";
		}
		else {
			out += "C";
		}
	}
	return out;
}

int main() {
	int people[5] = { 0,3,3,0,0 };
	queue<char> boat;
	cout << "EEECCC\\--/        ------" << endl;
	string l = "EEECCC";
	string r = "------";
	loadBoat(people, boat, l, r);
}