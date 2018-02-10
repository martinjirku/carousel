/*
 * Carousel_view.cpp
 *
 *  Created on: 10. 2. 2018
 *      Author: Martin Jirku
 */

#include "Carousel_view.h"
#include "diag/Trace.h"

Carousel_view::Carousel_view() {
	for (uint i = 0; i < sizeof(this->leds); i++) {
		STM_EVAL_LEDInit(this->leds[i]);
	}
}

void Carousel_view::On_carousel_change(int position) {
	this->Render(position);
}

void Carousel_view::Render(int& position) {
	trace_printf("Rendering LED number %u\n", position);
	this->Turn_off_leds();
	this->Turn_led_on(position);

}

void Carousel_view::Turn_off_leds() {
	for (uint i = 0; i < sizeof(this->leds); i++) {
		STM_EVAL_LEDOff(this->leds[i]);
	}
}

void Carousel_view::Turn_led_on(int led_id) {
	STM_EVAL_LEDOn(this->leds[led_id]);
}
