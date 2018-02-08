/*
 * Carousel.h
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#ifndef CAROUSEL_H_
#define CAROUSEL_H_

#include "AppLoop.h"

struct ERotation {
	enum type {
		CCW, ACW
	};
};

class Carousel : App {
typedef int degrees_per_second_t; // degrees per second

public:
	Carousel(AppLoop);
	void Start();
	void ToggleRotation();
	void WriteResponse();

	int getPosition() const;
	void setPosition(int);
	ERotation::type getRotation() const;
	void setRotation(ERotation::type rotation);
	degrees_per_second_t getSpeed() const;
	void setSpeed(degrees_per_second_t);

private:
	degrees_per_second_t speed = 180;
	int position = 0;
	ERotation::type rotation = ERotation::CCW;
};

#endif /* CAROUSEL_H_ */
