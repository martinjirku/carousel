/*
 * Carousel.cpp
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#include "Carousel.h"
#include "diag/Trace.h"

Carousel::Carousel(MJOS& os, Carousel_view& view) : MJApp(os) {
	this->view = view;
	this->speed = Carousel::DEFAULT_SPEED;
}

void Carousel::Toggle_rotation() {
	Set_rotation(position == ERotation::ACW ? ERotation::CCW : ERotation::ACW);
}

void Carousel::Start() {
//	this->os.Cancel_timer(this->async_id);
	this->async_id = this->os->Timer([&]() -> void {
		this->Set_next_position();
	}, this->speed, true);
}

void Carousel::Write_response() {
	trace_puts("This is a string comming from AppLoop");
}

int Carousel::Get_position() const {
	return position;
}

ERotation::type Carousel::Get_rotation() const {
	return rotation;
}
void Carousel::Set_next_position(){
	this->Set_position(this->position == Carousel::MAX_POSITION ? 0 : (this->position + 1));
}

void Carousel::Set_position(int pos) {
	this->position = pos;
	this->view.On_carousel_change(this->position);
}

void Carousel::Set_rotation(ERotation::type rotation = ERotation::CCW) {
	this->rotation = rotation;
}

void Carousel::Increase_speed(int add_speed_count) {
	this->speed += add_speed_count;
	this->Start();
}

void Carousel::Increase_speed() {
	this->Increase_speed(5);
}
