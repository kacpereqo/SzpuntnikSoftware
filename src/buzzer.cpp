#include "buzzer.hpp"
#include <Arduino.h>
#include "utils/constants.hpp"

Buzzer::Buzzer()
{
    this->pin = BUZZER_PIN;
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