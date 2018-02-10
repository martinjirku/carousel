/*
 * Carousel.h
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#pragma once

#include "MJApp.h"

struct ERotation {
	enum type {
		CCW, ACW
	};
};

class Carousel : MJApp {
typedef int degrees_per_second_t; // degrees per second

public:
	Carousel(MJOS& os);
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
