#include <Servo.h>
#include <Arduino.h>
#include "motor.hpp"

Servo myservo;

int pos = 0;

void motor_init()
{
    myservo.attach(SERVO_PIN);
    myservo.write(0);
}

// void motor_loop()
// {
//     for (pos = 0; pos <= 180; pos += 1)
//     {

//         myservo.write(pos);
//         delay(15);
//     }
//     for (pos = 180; pos >= 0; pos -= 1)
//     {
//         myservo.write(pos);
//         delay(15);
//     }
// }

void rotate(int angle)
{
    // Serial.print("rotated ");
    // Serial.print(angle);
    // Serial.print(" ");

    myservo.write(angle);
    // delay(50);
}