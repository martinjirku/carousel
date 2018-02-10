#pragma once

#include "STM32F3_Discovery/stm32f3_discovery.h"

class Carousel_view {
public:
	Carousel_view();
	void On_carousel_change(int position);
private:
	Led_TypeDef leds [8] = {	Led_TypeDef::LED3,
								Led_TypeDef::LED5,
								Led_TypeDef::LED7,
								Led_TypeDef::LED9,
								Led_TypeDef::LED10,
								Led_TypeDef::LED8,
								Led_TypeDef::LED6,
								Led_TypeDef::LED4 };
	void Render(int& position);
	void Turn_off_leds();
	void Turn_led_on(int);
};
