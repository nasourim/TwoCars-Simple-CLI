#include <iostream>

#include "Game.h"
using namespace std;

const char SCORE_CHARACTER = 'O';
const char GAME_OVER_CHARACTER = 'X';
const int ENTER_KEY = 13;
#include <conio.h>
int main() {
	Game twoCarsGame;
//	do {
		twoCarsGame.run();
		cout << endl << "GAME OVER!" << endl;
//		cout << endl << "PRESS ENTER TO RESTART! OR Another Key to End!" << endl;
//	} while (_getch() == ENTER_KEY);
	return 0;
}