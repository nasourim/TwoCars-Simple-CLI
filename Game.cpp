#include "Game.h"

Game::Game()
{
	this->score = 0;
	this->gameOver = false;
	this->action = STOP;
	bool equal;
	for (int i = 0; i < STAGE_NUMBER_OF_OBJECTS; i++) {
		this->obstacles[i].x = 2 * (rand() % 4) + 1;
		this->obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
		this->scores[i].x = 2 * (rand() % 4) + 1;
		this->scores[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
	}
	for (int i = 0; i < STAGE_NUMBER_OF_OBJECTS; i++) {
		equal = obstacles[i].x == this->scores[i].x && obstacles[i].y == this->scores[i].y;
		while (equal) {
			obstacles[i].x = 2 * (rand() % 4) + 1;
			obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			equal = obstacles[i].x == this->scores[i].x && obstacles[i].y == this->scores[i].y;
		}
		item_before[i] = scores[i];
		item_before[STAGE_NUMBER_OF_OBJECTS + i] = obstacles[i];
	}
}

void Game::run()
{
	this->drawTable();
	while (!this->gameOver)
	{
		this->updateTable();
		this->input();
		this->control();
		Sleep(100);
	}
}

void Game::drawTable()
{
	system("cls");
	for (int i = 0; i < TABLE_WIDTH + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < TABLE_HEIGHT; i++)
	{
		for (int j = 0; j < TABLE_WIDTH + 2; j++)
		{
			if (j == 0 || j == TABLE_WIDTH + 1) {
				cout << "#";
				continue;
			}
			else if (j == 2 || j == 4 || j == 6) {
				cout << "|";
				continue;
			}
			else if (i == CAR_ROW && (j == this->getLeftCarX() || j == this->getRightCarX())) {
				cout << "C";
				continue;
			}
			else
			{
				bool objectPrint = false;
				for (int k = 0; k < STAGE_NUMBER_OF_OBJECTS; k++)
				{
					bool isScore = false;
					if (scores[k].x == j && scores[k].y == i)
					{
						isScore = true;
						cout << "O";
						objectPrint = true;
					}
					if (!isScore && obstacles[k].x == j && obstacles[k].y == i)
					{
						cout << "X";
						objectPrint = true;
					}
				}
				if (!objectPrint)
					cout << " ";
			}

		}
		cout << endl;
	}

	for (int i = 0; i < TABLE_WIDTH + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << this->score << endl;
}

void Game::control()
{
	switch (action)
	{
	case LEFT_CAR:
		leftCar.swap();
		break;
	case RIGHT_CAR:
		rightCar.swap();
		break;
	case BOTH_CARS:
		leftCar.swap();
		rightCar.swap();
		break;
	default:
		break;
	}

	bool newObject = false;
	bool isScore = false;
	for (int i = 0; i < STAGE_NUMBER_OF_OBJECTS; i++) {
		if (this->obstacles[i].y == CAR_ROW && (this->obstacles[i].x == getLeftCarX() || this->obstacles[i].x == getRightCarX())) {
			gameOver = true;
		}

		if (this->scores[i].y == CAR_ROW && (this->scores[i].x == getLeftCarX() || this->scores[i].x == getRightCarX())) {
			this->score += 10;
			isScore = true;
			item_before[i] = scores[i];
			scores[i].x = 2*(rand() % 4) + 1;
			scores[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			newObject = true;
		}

		if (this->obstacles[i].y > CAR_ROW) {
			item_before[STAGE_NUMBER_OF_OBJECTS + i] = obstacles[i];
			obstacles[i].x = 2*(rand() % 4) + 1;
			obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			newObject = true;
		}

		if (this->obstacles[i].y > CAR_ROW) {
			item_before[STAGE_NUMBER_OF_OBJECTS + i] = obstacles[i];
			obstacles[i].x = 2*(rand() % 4) + 1;
			obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			newObject = true;
		}

		if (this->scores[i].y > CAR_ROW && !isScore) {
			gameOver = true;
		}

		if (this->scores[i].y > CAR_ROW) {
			item_before[i] = scores[i];
			scores[i].x = 2*(rand() % 4) + 1;
			scores[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			newObject = true;
		}

		if (!newObject) {
			item_before[i] = scores[i];
			item_before[STAGE_NUMBER_OF_OBJECTS + i] = obstacles[i];
			scores[i].y++;
			obstacles[i].y++;
		}

	}

}

void Game::input() {
	if (_kbhit()) {
		switch (_getch()) {
		case SWAP_LEFT_CAR:
			action = LEFT_CAR;
			break;
		case SWAP_RIGHT_CAR:
			action = RIGHT_CAR;
			break;
		case SWAP_BOTH_CARS:
			action = BOTH_CARS;
			break;
		case ESCAPE_KEY:
			this->gameOver = true;
			break;
		case 224:
			switch (_getch())
			{
			case 75:
				action = LEFT_CAR;
				break;
			case 77:
				action = RIGHT_CAR;
				break;
			case 72:
				action = BOTH_CARS;
				break;
			case 80:
				action = BOTH_CARS;
				break;
			default:
				break;
			}
			break;
		default:
			this->action = NOTHING;
			break;
		}
	}
	else {
		this->action = NOTHING;
	}
}

int Game::getLeftCarX()
{
	if (leftCar.position == LEFT) {
		return LEFT_CAR_LEFT_X;
	}
	return LEFT_CAR_RIGHT_X;
}

int Game::getRightCarX()
{
	if (rightCar.position == LEFT) {
		return RIGHT_CAR_LEFT_X;
	}
	return RIGHT_CAR_RIGHT_X;
}

void Game::updateTable() {
	
	for (Coordinate item : item_before){
		if (item.y <= 0 || item.y > CAR_ROW + 1){
			continue;
		}
		printObjects(item.x, item.y, ' ');
	}
	
	for (Coordinate scoreItem : scores){
		if (scoreItem.y <= 0 || scoreItem.y > CAR_ROW ) {
			continue;
		}
		printObjects(scoreItem.x, scoreItem.y, 'O');
	}

	for (Coordinate obstacleItem : obstacles){
		if (obstacleItem.y <= 0 || obstacleItem.y > CAR_ROW ) {
			continue;
		}
		printObjects(obstacleItem.x, obstacleItem.y, 'X');
	}
	/*
	for (int i = 0; i < TABLE_HEIGHT; i++)
	{
		for (int j = 0; j < TABLE_WIDTH + 2; j++)
		{
			if (j == 0 || j == TABLE_WIDTH + 1) {
				continue;
			}
			else if (j == 2 || j == 4 || j == 6) {
				continue;
			}
			else if (i == CAR_ROW && (j == this->getLeftCarX() || j == this->getRightCarX())) {
				continue;
			}
			else
			{
				for (int k = 0; k < STAGE_NUMBER_OF_OBJECTS; k++)
				{
					bool isScore = false;
					if (scores[k].x == j && scores[k].y == i)
					{
						isScore = true;
						conGoXY(j, i);
						cout << "O";
					}
					if (!isScore && obstacles[k].x == j && obstacles[k].y == i)
					{
						conGoXY(j, i);
						cout << "X";
					}
				}
			}
			
		}
	}
	*/

	printCars();
	printScore();
	
}
/*
void Game::conPrintXY(int x, int y, char c) {
	
//	COORD coord;
//	coord.X = x;
//	coord.Y = y;
//	SetConsoleCursorPosition(
//			GetStdHandle( STD_OUTPUT_HANDLE ),
//			coord
//	);
	
	DWORD dw;
	COORD here;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
	{
//		printf("Invalid handle");
	}
	here.X = x;
	here.Y = y;
	LPCSTR lp_cstr;
	switch (c)
	{
	case 'O':
		lp_cstr = "O";
		break;
	case 'X':
		lp_cstr = "X";
		break;
	case 'C':
		lp_cstr = "C";
		break;
	case ' ':
		lp_cstr = " ";
		break;
	default:
		lp_cstr = "|";
		break;
	}
	WriteConsoleOutputCharacter(hStdOut, lp_cstr, 1, here, &dw);
}
*/

void Game::printXY(int x, int y, LPCSTR lp_cstr, int length) {
	
	DWORD dw;
	COORD here;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
	{
		//		printf("Invalid handle");
	}
	here.X = x;
	here.Y = y;
	WriteConsoleOutputCharacter(hStdOut, lp_cstr, length, here, &dw);
	
}

void Game::printObjects(int x, int y, char character) {
	LPCSTR lp_cstr;
	switch (character)
	{
	case 'O':
		lp_cstr = "O";
		break;
	case 'X':
		lp_cstr = "X";
		break;
	case ' ':
		lp_cstr = " ";
		break;
	default:
		lp_cstr = "|";
		break;
	}
	printXY(x, y, lp_cstr, 1);
	
}

void Game::printScore()
{
	string nowScore = "Score: " + to_string(score);
	LPCSTR lp_cstr = nowScore.c_str();
	printXY(0, CAR_ROW + 3, lp_cstr, nowScore.length());
}

void Game::printCars()
{
	LPCSTR car = "C";
	LPCSTR empty = " ";
	if (rightCar.position == LEFT) {
		printXY(RIGHT_CAR_LEFT_X, CAR_ROW + 1, car, 1);
		printXY(RIGHT_CAR_RIGHT_X, CAR_ROW + 1, empty, 1);
	}
	else
	{
		printXY(RIGHT_CAR_LEFT_X, CAR_ROW + 1, empty, 1);
		printXY(RIGHT_CAR_RIGHT_X, CAR_ROW + 1, car, 1);
	}
	if (leftCar.position == LEFT) {
		printXY(LEFT_CAR_LEFT_X, CAR_ROW + 1, car, 1);
		printXY(LEFT_CAR_RIGHT_X, CAR_ROW + 1, empty, 1);
	}
	else
	{
		printXY(LEFT_CAR_LEFT_X, CAR_ROW + 1, empty, 1);
		printXY(LEFT_CAR_RIGHT_X, CAR_ROW + 1, car, 1);
	}
}



