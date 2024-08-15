#include "timer.hpp"
#include "Arduino.h"

void Timer::start()
{
    this->launch_time = millis();
}

bool Timer::doesTimeElapsed(uint32_t time)
{
    this->current_time = millis();
    return this->current_time - this->launch_time >= time;
}