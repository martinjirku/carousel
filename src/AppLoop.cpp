/*
 * AppLoop.cpp
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#include "AppLoop.h"
#include <map>
#include <vector>
#include "diag/Trace.h"

AppLoop::AppLoop() {
	// Use SysTick as reference for the delay loops.
	SysTick_Config(SystemCoreClock / FREQUENCY_HZ);
	timeouts = std::map<async_id_t, CallbackItem*>();
}

AppLoop App::getAppLoop() const {
	return appLoop;
}

void AppLoop::start() {
	while(true) {
		currentTime++;
		// find timeouts to remove
		std::vector<async_id_t> timesToRemove {};
		trace_printf("SIZE FROM app loop: %u s\n", timeouts.size());
		for (auto const& it: timeouts) {
			trace_printf("lastTick: %u s\n", it.second->lastTick);
			if (it.second->lastTick == currentTime) {
				timesToRemove.push_back(it.first);
			}
		}
		// remove found timeouts and run;
		for(auto const& value: timesToRemove) {
			timeouts[value]->fn();
			timeouts.erase(value);
		}
		trace_printf("Current time: %u s\n", currentTime);
	}
}

void AppLoop::setTimeout(std::function<void ()>	fn, ticks_t time) {
	CallbackItem* cbItem = new CallbackItem();
	cbItem->fn = fn;
	cbItem->lastTick = time + currentTime;

	timeouts[ids] = cbItem;
	trace_printf("SIZE: %u s\n", timeouts.size());
	ids++;
}

App::App(AppLoop aloop) {
	appLoop = aloop;
}
