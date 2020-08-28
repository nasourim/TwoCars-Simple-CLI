#ifndef TWOCARS_GAME_H
#define TWOCARS_GAME_H

#include <iostream>
#include <conio.h>
#include <windows.h>

#include "Car.h"
#include "Coordinate.h"

const int TABLE_HEIGHT = 21;
const int TABLE_WIDTH = 7;
const int SWAP_LEFT_CAR = 'a';
const int SWAP_RIGHT_CAR = 'd';
const int SWAP_BOTH_CARS = 32;
const int ESCAPE_KEY = 27;
const int CAR_ROW = 20;
const int LEFT_CAR_LEFT_X = 1;
const int LEFT_CAR_RIGHT_X = 3;
const int RIGHT_CAR_LEFT_X = 5;
const int RIGHT_CAR_RIGHT_X = 7;
const int STAGE_NUMBER_OF_OBJECTS = 3;
enum ACTION {STOP, LEFT_CAR, RIGHT_CAR, BOTH_CARS, NOTHING};
using namespace std;

class Game {
private:
	Car leftCar;
	Car rightCar;
	Coordinate obstacles[STAGE_NUMBER_OF_OBJECTS];
	Coordinate scores[STAGE_NUMBER_OF_OBJECTS];
	Coordinate item_before[STAGE_NUMBER_OF_OBJECTS*2];
	int score;
	bool gameOver;
	ACTION action;

public:
	Game();
	~Game() = default;
	void run();
	void drawTable();
	void updateTable();
	void control();
	void input();
	int getLeftCarX();
	int getRightCarX();
	static void printXY(int x, int y, LPCSTR lp_cstr, int length);
	static void printObjects(int x, int y, char c);
	void printScore();
	void printCars();

};


#endif //TWOCARS_GAME_H
