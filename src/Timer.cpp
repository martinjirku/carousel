/*
 * Timer.cpp
 *
 *  Created on: 3. 2. 2018
 *      Author: Martin Jirku
 */

#include "Timer.h"

volatile Timer::ticks_t Timer::ms_delayCount;

void Timer::sleep(ticks_t ticks)
{
  ms_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (ms_delayCount != 0u)
    ;
}
