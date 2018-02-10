/*
 * AppLoop.cpp
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#include "MJOS.h"
#include <vector>
#include "diag/Trace.h"

MJOS::MJOS() {
	// Use SysTick as reference for the delay loops.
	SysTick_Config(SystemCoreClock / FREQUENCY_HZ);
}

void MJOS::Start() {
	while(true) {
		current_time++;
		// find timeouts to reschedule or delay
		std::vector<async_id_t> timersToRemove {};
		for (auto const& it: this->timers) {
			if (it.second.lastTick == current_time) {
				timersToRemove.push_back(it.first);
			}
		}
		// remove found timeouts and run;
		for(auto const& value: timersToRemove) {
			timers[value].fn();
			if (timers[value].repeat) {
				timers[value].lastTick = current_time + timers[value].delay;
			} else {
				this->Cancel_timer(value);
			}
		}
	}
}

async_id_t MJOS::Timer(std::function<void ()> callback, ticks_t time, bool repeat) {
	ids++;
	ticks_t transformed_time = time * 100;
	this->timers[ids] = Timer_entry { callback,  transformed_time, transformed_time + current_time, repeat };
	return ids;
}

async_id_t MJOS::Timer(std::function<void ()> callback, ticks_t time) {
	return this->Timer(callback, time, false);
}

void MJOS::Cancel_timer(async_id_t timer_id) {
	// todo: does it really remove from memory?
	this->timers.erase(timer_id);
}





