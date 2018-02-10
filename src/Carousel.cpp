/*
 * Carousel.cpp
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#include "Carousel.h"
#include "diag/Trace.h"

Carousel::Carousel(MJOS &os) : MJApp(os) {
	uint32_t i = 4;
	ticks_t time = 10;
	os.timer([&]() -> void {
		trace_printf("comming from lambda %u", i);
	}, time);
}

void Carousel::ToggleRotation() {
	setRotation(position == ERotation::ACW ? ERotation::CCW : ERotation::ACW);
}

void Carousel::Start() {
	trace_puts("Registering a function");
}

void Carousel::WriteResponse() {
	trace_puts("This is a string comming from AppLoop");
}

int Carousel::getPosition() const {
	return position;
}

void Carousel::setPosition(int position = 0) {
	this->position = position;
}

ERotation::type Carousel::getRotation() const {
	return rotation;
}

void Carousel::setRotation(ERotation::type rotation = ERotation::CCW) {
	this->rotation = rotation;
}

Carousel::degrees_per_second_t Carousel::getSpeed() const {
	return speed;
}
void Carousel::setSpeed(Carousel::degrees_per_second_t speed = 180) {
	this->speed = speed;
}
