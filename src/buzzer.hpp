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
    uint64_t lastUpdate;
    uint16_t frequency;
    void play(int frequency, int duration);
    uint8_t pin;
    uint16_t note;
};