#include "Coordinate.h"

Coordinate::Coordinate() {
	this->x = 0;
	this->y = 0;
}

Coordinate::Coordinate(int x_coordinate, int y_coordinate) {
	this->x = x_coordinate;
	this->y = y_coordinate;
}

void Coordinate::operator=( Coordinate &rhs )
{
	this->x = rhs.x;
	this->y = rhs.y;
}
