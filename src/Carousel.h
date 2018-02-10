/*
 * Carousel.h
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#pragma once

#include "MJApp.h"
#include "Carousel_view.h"

struct ERotation {
	enum type {
		CCW, ACW
	};
};

class Carousel : MJApp {

public:
	Carousel(MJOS& os, Carousel_view& view);
	void Start();
	void Toggle_rotation();
	void Write_response();

	int Get_position() const;
	ERotation::type Get_rotation() const;
	void Set_rotation(ERotation::type rotation);
	void Increase_speed();
	void Increase_speed(int);

private:
	static constexpr int MAX_POSITION = 7;
	static constexpr int DEFAULT_SPEED = 125;

	ticks_t speed;
	async_id_t async_id = 0;
	Carousel_view view;

	int position = 0;
	ERotation::type rotation = ERotation::CCW;
	void Set_next_position();
	void Set_position(int position);
};
