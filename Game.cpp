#include "Game.h"

Game::Game()
{
	this->score = 0;
	this->gameOver = false;
	this->action = STOP;
	bool equal;
	for (int i = 0; i < STAGE_NUMBER_OF_OBJECTS; i++) {
		this->obstacles[i].x = rand() % 4 + 2;
		this->obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
		this->scores[i].x = rand() % 4 + 2;
		this->scores[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
	}
	for (int i = 0; i < STAGE_NUMBER_OF_OBJECTS; i++) {
		equal = obstacles[i].x == this->scores[i].x && obstacles[i].y == this->scores[i].y;
		while (equal) {
			obstacles[i].x = rand() % 4 + 2;
			obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			equal = obstacles[i].x == this->scores[i].x && obstacles[i].y == this->scores[i].y;
		}
	}
}

void Game::run()
{
	while (!this->gameOver)
	{
		this->drawTable();
		this->input();
		this->control();
		Sleep(10);
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

	for (int i = 0; i < TABLE_WIDTH; i++)
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
	for (int i = 0; i < STAGE_NUMBER_OF_OBJECTS; i++) {
		if (this->obstacles[i].y == CAR_ROW && (this->obstacles[i].x == getLeftCarX() || this->obstacles[i].x == getRightCarX())) {
			gameOver = true;
		}

		if (this->scores[i].y == CAR_ROW && (this->scores[i].x == getLeftCarX() || this->scores[i].x == getRightCarX())) {
			this->score += 10;
			scores[i].x = rand() % 4 + 2;
			scores[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			newObject = true;
		}

		if (this->obstacles[i].y > CAR_ROW) {
			obstacles[i].x = rand() % 4 + 2;
			obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			newObject = true;
		}

		if (this->obstacles[i].y > CAR_ROW) {
			obstacles[i].x = rand() % 4 + 2;
			obstacles[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			newObject = true;
		}

		if (this->scores[i].y > CAR_ROW) {
			scores[i].x = rand() % 4 + 2;
			scores[i].y = rand() % TABLE_HEIGHT - TABLE_HEIGHT;
			newObject = true;
		}

		if (!newObject) {
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
