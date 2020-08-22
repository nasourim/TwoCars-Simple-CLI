#include "Car.h"

Car::Car() {
	this->position = DEFAULT_POSITION;
}

void Car::swap() {
	if (this->position == LEFT)
		this->position = RIGHT;
	else if (this->position == RIGHT)
		this->position = LEFT;
}
