#pragma once
#include <cstdint>

class Timer
{
private:
    uint32_t launch_time;
    uint32_t current_time;

public:
    void start();
    bool doesTimeElapsed(uint32_t time);
};