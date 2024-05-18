#ifndef SPEAKER_HPP
#define SPEAKER_HPP

#include <Arduino.h>
#include "pitches.h"

constexpr int SPEAKER_PIN = 9;

struct Speaker
{

    unsigned int count = 0;

    void play()
    {
        int noteDuration = 1000 / noteDurations[this->count];
        tone(SPEAKER_PIN, melody[this->count], noteDuration);
        delay(noteDuration * 1.30);
        noTone(SPEAKER_PIN);
        this->count++;
        if (this->count == sizeof(melody) / sizeof(melody[0]))
        {
            this->count = 0;
        }
    }
};

#endif // SPEAKER_HPP