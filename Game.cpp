#include "Game.h"

Game::Game()
{
	this->score = 0;
	this->gameOver = false;
	this->action = STOP;
	for (int i = 0; i < STAGE_NUMBER_OF_OBJECTS; i++) {
		this->obstacles[i].x = 2 * (rand() % 4) + 1;
		this->obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
		this->scores[i].x = 2 * (rand() % 4) + 1;
		this->scores[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
	}
	for (int i = 0; i < STAGE_NUMBER_OF_OBJECTS; i++) {
		bool equal = obstacles[i].x == this->scores[i].x && obstacles[i].y == this->scores[i].y;
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

void Game::drawTable() const
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

int Game::getLeftCarX() const
{
	if (leftCar.position == LEFT) {
		return LEFT_CAR_LEFT_X;
	}
	return LEFT_CAR_RIGHT_X;
}

int Game::getRightCarX() const
{
	if (rightCar.position == LEFT) {
		return RIGHT_CAR_LEFT_X;
	}
	return RIGHT_CAR_RIGHT_X;
}

void Game::updateTable() {
	
	for (auto item : item_before){
		if (item.y <= 0 || item.y > CAR_ROW + 1){
			continue;
		}
		printObjects(item.x, item.y, ' ');
	}
	
	for (auto scoreItem : scores){
		if (scoreItem.y <= 0 || scoreItem.y > CAR_ROW ) {
			continue;
		}
		printObjects(scoreItem.x, scoreItem.y, 'O');
	}

	for (auto obstacleItem : obstacles){
		if (obstacleItem.y <= 0 || obstacleItem.y > CAR_ROW ) {
			continue;
		}
		printObjects(obstacleItem.x, obstacleItem.y, 'X');
	}

	printCars();
	printScore();
	
}

void Game::printXY(const int x, const int y, const LPCSTR write_string, const int length) {
	
	DWORD dword;
	COORD whereToGo;
	HANDLE outputHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	whereToGo.X = x;
	whereToGo.Y = y;
	WriteConsoleOutputCharacter(outputHandler, write_string, length, whereToGo, &dword);
	
}

void Game::printObjects(const int x, const int y, char character) {
	LPCSTR characterToWrite;
	switch (character)
	{
	case 'O':
		characterToWrite = "O";
		break;
	case 'X':
		characterToWrite = "X";
		break;
	case ' ':
		characterToWrite = " ";
		break;
	default:
		characterToWrite = "|";
		break;
	}
	printXY(x, y, characterToWrite, 1);
	
}

void Game::printScore() const
{
	const string nowScore = "Score: " + to_string(score);
	const LPCSTR scoreString = nowScore.c_str();
	printXY(0, CAR_ROW + 3, scoreString, nowScore.length());
}

void Game::printCars() const
{
	const LPCSTR car = "C";
	const LPCSTR empty = " ";
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



