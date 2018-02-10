/*
 * AppLoop.h
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#pragma once

#include <functional>
#include <map>
#include "cmsis_device.h"


typedef uint32_t ticks_t;
typedef uint32_t async_id_t;

struct TimerEntry {
	std::function<void ()> fn;
	ticks_t delay;
	ticks_t lastTick;
	bool repeat;
};

class MJOS {
public:
  MJOS();
  void start();
  async_id_t timer(std::function<void ()> callback, ticks_t time);
  async_id_t timer(std::function<void ()> callback, ticks_t time, bool repeat);
  void cancelTimer(async_id_t);

private:
  static constexpr ticks_t FREQUENCY_HZ = 1000u;
  std::map<async_id_t, TimerEntry> timers = {};
  async_id_t ids = 0;
  ticks_t currentTime = 0;

};
