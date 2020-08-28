#ifndef TWOCARS_CAR_H
#define TWOCARS_CAR_H

#include <string>

enum POSITION { LEFT, RIGHT };
const POSITION DEFAULT_POSITION = LEFT;

using namespace std;

class Car {

public:
	POSITION position;
	void swap();
	Car();
	~Car() = default;

};


#endif //TWOCARS_CAR_H

