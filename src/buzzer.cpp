#include "buzzer.hpp"
#include <Arduino.h>

Buzzer::Buzzer()
{
    this->pin = D5;
    pinMode(this->pin, OUTPUT);
}

void Buzzer::buzz()
{
    digitalWrite(this->pin, HIGH);
}

void Buzzer::stop()
{
    digitalWrite(this->pin, LOW);
}

void Buzzer::play(int frequency, int duration)
{
    tone(this->pin, frequency, duration);
}

void Buzzer::playNyanCat()
{
    ;
}