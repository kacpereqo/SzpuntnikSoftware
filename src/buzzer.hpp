#pragma once
#include <cstdint>

class Buzzer
{
public:
    Buzzer();
    void buzz();
    void stop();
    void playNyanCat();

private:
    void play(int frequency, int duration);
    uint8_t pin;
};