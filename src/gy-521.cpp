#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "gy-521.hpp"

Adafruit_MPU6050 mpu;

float degreeY = 0;
float degreeX = 0;
float degreeZ = 0;

float gyroOffsetX = 0;
float gyroOffsetY = 0;
float gyroOffsetZ = 0;

float avgGyroX = 0;
float avgGyroY = 0;
float avgGyroZ = 0;

bool fullData = false;

unsigned long lastTime = 0;
unsigned long currentTime = 0;

unsigned short dataCounter = 0;

char accMainAxis = '\0';

GY_521 data[DATA_SIZE] = {};

float radiansToDegrees(float radians)
{
    return radians * 180 / M_PI;
}

void mpu_init()
{

    while (!Serial)
        delay(10);

    Serial.println("MPU6050 FOUND!!!");

    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }

    Serial.println("MPU6050 CALIBRATING");

    float tempAccX = 0;
    float tempAccY = 0;
    float tempAccZ = 0;

    for (size_t i = 0; i < GY_521_INIT_PRECISION; i++)
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        gyroOffsetX += g.gyro.x;
        gyroOffsetY += g.gyro.y;
        gyroOffsetZ += g.gyro.z;

        tempAccX += a.acceleration.x;
        tempAccY += a.acceleration.y;
        tempAccZ += a.acceleration.z;
    }

    if (tempAccX > tempAccY && tempAccX > tempAccZ)
    {
        accMainAxis = 'x';
    }
    else if (tempAccY > tempAccX && tempAccY > tempAccZ)
    {
        accMainAxis = 'y';
    }
    else
    {
        accMainAxis = 'z';
    }
    gyroOffsetX /= GY_521_INIT_PRECISION;
    gyroOffsetY /= GY_521_INIT_PRECISION;
    gyroOffsetZ /= GY_521_INIT_PRECISION;

    Serial.println("MPU6050 CALIBRATED");
    Serial.println("");

    delay(100);
}

double accAngle(const sensors_event_t &acc, const char axis)
{
    double angle = 0;

    // combine axis and main axis

    if (axis == 'x' && accMainAxis == 'x')
    {
        angle = atan(acc.acceleration.y / sqrt(acc.acceleration.x * acc.acceleration.x + acc.acceleration.z * acc.acceleration.z));
    }
    else if (axis == 'y' && accMainAxis == 'y')
    {
        angle = atan(acc.acceleration.x / sqrt(acc.acceleration.y * acc.acceleration.y + acc.acceleration.z * acc.acceleration.z));
    }
    else if (axis == 'z' && accMainAxis == 'z')
    {
        angle = atan(sqrt(acc.acceleration.x * acc.acceleration.x + acc.acceleration.y * acc.acceleration.y) / acc.acceleration.z);
    }
    else if (axis == 'x' && accMainAxis == 'y')
    {
        angle = atan(acc.acceleration.z / sqrt(acc.acceleration.x * acc.acceleration.x + acc.acceleration.y * acc.acceleration.y));
    }
    else if (axis == 'x' && accMainAxis == 'z')
    {
        angle = atan(acc.acceleration.y / sqrt(acc.acceleration.x * acc.acceleration.x + acc.acceleration.z * acc.acceleration.z));
    }
    else if (axis == 'y' && accMainAxis == 'x')
    {
        angle = atan(acc.acceleration.z / sqrt(acc.acceleration.x * acc.acceleration.x + acc.acceleration.y * acc.acceleration.y));
    }
    else if (axis == 'y' && accMainAxis == 'z')
    {
        angle = atan(acc.acceleration.x / sqrt(acc.acceleration.y * acc.acceleration.y + acc.acceleration.z * acc.acceleration.z));
    }
    else if (axis == 'z' && accMainAxis == 'x')
    {
        angle = atan(sqrt(acc.acceleration.y * acc.acceleration.y + acc.acceleration.z * acc.acceleration.z) / acc.acceleration.x);
    }
    else if (axis == 'z' && accMainAxis == 'y')
    {
        angle = atan(sqrt(acc.acceleration.x * acc.acceleration.x + acc.acceleration.z * acc.acceleration.z) / acc.acceleration.y);
    }

    return angle * 180 / M_PI;
}

void mpu_loop()
{
    sensors_event_t a, g, temp;

    GY_521 avgData = {};

    mpu.getEvent(&a, &g, &temp);

    data[dataCounter].accelX = a.acceleration.x;
    data[dataCounter].accelY = a.acceleration.y;
    data[dataCounter].accelZ = a.acceleration.z;

    data[dataCounter].gyroX = g.gyro.x - gyroOffsetX;
    data[dataCounter].gyroY = g.gyro.y - gyroOffsetY;
    data[dataCounter].gyroZ = g.gyro.z - gyroOffsetZ;

    dataCounter = (dataCounter + 1) % DATA_SIZE;

    if (dataCounter == DATA_SIZE - 1)
    {
        fullData = true;
    }

    if (fullData)
    {
        for (size_t i = 0; i < DATA_SIZE; i++)
        {
            avgData.accelX += data[i].accelX;
            avgData.accelY += data[i].accelY;
            avgData.accelZ += data[i].accelZ;

            avgData.gyroX += data[i].gyroX;
            avgData.gyroY += data[i].gyroY;
            avgData.gyroZ += data[i].gyroZ;
        }

        avgData.accelX /= DATA_SIZE;
        avgData.accelY /= DATA_SIZE;
        avgData.accelZ /= DATA_SIZE;

        avgData.gyroX /= DATA_SIZE;
        avgData.gyroY /= DATA_SIZE;
        avgData.gyroZ /= DATA_SIZE;

        currentTime = millis();
        float elapsedTime = (currentTime - lastTime) / 1000.0;

        degreeX = 0.93 * (degreeX + avgData.gyroX * elapsedTime) + 0.07 * accAngle(a, 'x');
        degreeY = 0.93 * (degreeY + avgData.gyroY * elapsedTime) + 0.07 * accAngle(a, 'y');
        degreeZ = 0.93 * (degreeZ + avgData.gyroZ * elapsedTime) + 0.07 * accAngle(a, 'z');

        lastTime = currentTime;

        delay(5);
    }

#ifdef GY_521_DEBUG
    Serial.print("");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print("");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print("");
    Serial.print(a.acceleration.z);
    Serial.print(", ");
    Serial.print("");
    Serial.print(g.gyro.x - gyroOffsetX);
    Serial.print(",");
    Serial.print("");
    Serial.print(g.gyro.y - gyroOffsetY);
    Serial.print(",");
    Serial.print("");
    Serial.print(g.gyro.z - gyroOffsetZ);
    Serial.print(", ");
    Serial.print("");
    Serial.print("degx:");
    Serial.print(degreeX);
    Serial.print(", degy:");
    Serial.print(degreeY);
    Serial.print(", degz:");
    Serial.print(degreeZ);

    Serial.println("");
    delay(30);

#endif
}
