#pragma once
#include "Servo.h"

class Recovery
{
    // private:

public:
    Servo servo;
    enum TriggeredBy
    {
        Timer,
        Altitude,
        Rotation,
        Manual,
    };

    Recovery();
    void test();
    void deploy(TriggeredBy trigger);
};