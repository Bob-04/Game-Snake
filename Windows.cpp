#include "GameSnakeHeader.h"
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// check if the string is a number
bool isDigit(std::string str) {
	return !str.empty() && 
		std::find_if(str.begin(), str.end(), [](char c) { return !std::isdigit(c); }) == str.end();
}

void startingWindwow(const int bestScore, int& sizeField, int& difficult)
{
	setCursorPosition(1, 0, 10);
	cout << "Game 'Snake'  (Osadchuk, 2018)";

	setCursorPosition(1, 3, 15);
	cout << "Rules of the game:" << endl;
	cout << "You need to manage a snake and eat fruits (*)." << endl;
	cout << "Game finished, if you crash into the wall or into yourself" << endl;

	setCursorPosition(1, 7, 14);
	cout << "Control:" << endl;
	cout << "KEY_LEFT  - Move left" << endl;
	cout << "KEY_RIGHT - Move right" << endl;
	cout << "KEY_UP    - Move up" << endl;
	cout << "KEY_DOWN  - Move down" << endl;

	setCursorPosition(1, 14, 11);
	cout << "Best score: " << bestScore;

	setCursorPosition(0, 17, 12);
	cout << "Choose the size of field (6 - 50): ";
	while (true) { // read the size of the field from the console
		std::string sizeFieldString;
		cin >> sizeFieldString;

		if (isDigit(sizeFieldString)) {
			sizeField = atoi(sizeFieldString.c_str());
			if (sizeField >= 6 && sizeField <= 50)
				break;
		}

		clearLine(17);
		setCursorPosition(0, 17, 3);
		cout << "Size of field must be (6 - 50): ";
	}

	setCursorPosition(0, 18, 12);
	cout << "Choose the difficulty (1 - 10): ";
	while (true) { // read the difficult from the console
		std::string difficultString;
		cin >> difficultString;

		if (isDigit(difficultString)) {
			difficult = atoi(difficultString.c_str());
			if (difficult >= 1 && difficult <= 10)
				break;
		}

		clearLine(18);
		setCursorPosition(0, 18, 3);
		cout << "Difficult must be (1 - 10): ";
	}

	setCursorPosition(0, 20, 13);
	cout << "Please, expand console window\n" << endl;
	cout << "Press to start !";
	return;
}

void finishWindwow(const int score, const bool isWin, int& bestScore)
{
	system("cls");
	setCursorPosition(2, 1, 12);

	cout << (isWin ? "You are winner !!!" : "You lost((");

	setCursorPosition(2, 3, 10);
	if (bestScore < score) {
		bestScore = score;
		static std::ofstream out;
		CreateDirectory("res", NULL);
		out.open("res/best.score");
		if (out.is_open()) {
			out << bestScore; // write the best score to file
		}
		out.close();
		cout << "It's a new record -  " << bestScore;
	}
	else {
		cout << "Your score is -  " << score;
	}

	setCursorPosition(0, 5, 13);
	cout << "Press smth to continue  ('0' to exit): ";
	char finish(0); cin >> finish;
	if (finish == '0')
		exit(0);
	system("cls");
}