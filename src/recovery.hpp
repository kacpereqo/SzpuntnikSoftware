#pragma once
#include "Servo.h"

class Recovery
{
private:
    Servo servo;

public:
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