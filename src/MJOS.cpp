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

void MJOS::start() {
	while(true) {
		currentTime++;
		// find timeouts to reschedule or delay
		std::vector<async_id_t> timersToRemove {};
		for (auto const& it: this->timers) {
			if (it.second.lastTick == currentTime) {
				timersToRemove.push_back(it.first);
			}
		}
		// remove found timeouts and run;
		for(auto const& value: timersToRemove) {
			timers[value].fn();
			if (timers[value].repeat) {
				timers[value].lastTick = currentTime + timers[value].delay;
			} else {
				this->cancelTimer(value);
			}
		}
	}
}

async_id_t MJOS::timer(std::function<void ()> callback, ticks_t time, bool repeat) {
	ids++;
	this->timers[ids] = TimerEntry { callback,  time, time + currentTime, repeat };
	return ids;
}

async_id_t MJOS::timer(std::function<void ()> callback, ticks_t time) {
	return this->timer(callback, time, false);
}

void MJOS::cancelTimer(async_id_t timer_id) {
	// todo: does it really remove from memory?
	this->timers.erase(timer_id);
}





