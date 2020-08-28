#ifndef TWOCARS_COORDINATE_H
#define TWOCARS_COORDINATE_H


class Coordinate {
public:
	int x;
	int y;
	Coordinate();
	Coordinate(int x_coordinate, int y_coordinate);
	~Coordinate() = default;
	void operator = (Coordinate &rhs);
};


#endif //TWOCARS_COORDINATE_H
