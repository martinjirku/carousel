/*
 * AppLoop.h
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#ifndef APPLOOP_H_
#define APPLOOP_H_

#include <functional>
#include <map>
#include "cmsis_device.h"


typedef uint32_t ticks_t;

struct CallbackItem {
	ticks_t lastTick;
	std::function<void ()> fn;
};

class AppLoop {
public:
  typedef uint32_t async_id_t;
  static constexpr ticks_t FREQUENCY_HZ = 1000u;

  AppLoop();
  void setTimeout(std::function<void ()>, ticks_t);
  void cancelAsync(async_id_t);
  void start();

private:
  std::map<async_id_t, CallbackItem*> timeouts;
  async_id_t ids = 0;
  ticks_t currentTime = 0;

};

class App {
public:
	App(AppLoop appLoop);
	AppLoop getAppLoop() const;


protected:
	AppLoop appLoop;
};

#endif /* APPLOOP_H_ */
