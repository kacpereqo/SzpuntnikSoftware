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

Data dataArr[DATA_SIZE] = {};

float radiansToDegrees(float radians)
{
    return radians * 180 / M_PI;
}

void mpu_init()
{

    while (!Serial)
        delay(10);

    Serial.println("Adafruit MPU6050 test!");

    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }

    for (size_t i = 0; i < GY_521_INIT_PRECISION; i++)
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        gyroOffsetX += g.gyro.x;
        gyroOffsetY += g.gyro.y;
        gyroOffsetZ += g.gyro.z;
    }

    gyroOffsetX /= GY_521_INIT_PRECISION;
    gyroOffsetY /= GY_521_INIT_PRECISION;
    gyroOffsetZ /= GY_521_INIT_PRECISION;

    Serial.println("MPU6050 Found!");

    Serial.println("");
    delay(100);
}

void mpu_loop()
{
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    dataArr[dataCounter].x = g.gyro.x;
    dataArr[dataCounter].y = g.gyro.y;
    dataArr[dataCounter].z = g.gyro.z;

    dataCounter = (dataCounter + 1) % DATA_SIZE;

    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        avgGyroX += dataArr[i].x;
        avgGyroY += dataArr[i].y;
        avgGyroZ += dataArr[i].z;
    }

    avgGyroX /= DATA_SIZE;
    avgGyroY /= DATA_SIZE;
    avgGyroZ /= DATA_SIZE;

    if (dataCounter == 24)
    {
        fullData = true;
    }

    currentTime = millis();
    float elapsedTime = (currentTime - lastTime);
    lastTime = currentTime;

    if (fullData)
    {
        degreeX += (avgGyroX - gyroOffsetX) * elapsedTime;
        degreeY += (avgGyroY - gyroOffsetY) * elapsedTime;
        degreeZ += (avgGyroZ - gyroOffsetZ) * elapsedTime;
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
    Serial.print(radiansToDegrees(degreeX) / 1000);
    Serial.print(",");
    Serial.print("");
    Serial.print(radiansToDegrees(degreeY) / 1000);
    Serial.print(",");
    Serial.print("");
    Serial.print(radiansToDegrees(degreeZ) / 1000);
    Serial.println("");
    delay(30);

#endif
}
