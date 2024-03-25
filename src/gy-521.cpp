#pragma once

#include "gy-521.hpp"
// #define MPU6050_DEBUG

float offsetGyroX, offsetGyroY, offsetGyroZ;

Adafruit_MPU6050 mpu;

Position degrees;
int8_t counter = 0;
SensorData data[DATA_SIZE];

unsigned long lastTime = 0;

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
    Serial.println("MPU6050 Found!");

    // setupt motion detection
    mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
    mpu.setMotionDetectionThreshold(1);
    mpu.setMotionDetectionDuration(20);

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    for (int i = 0; i < GYRO_OFFSET_PRECISION; i++)
    {
        mpu.getEvent(&a, &g, &temp);
        offsetGyroX += g.gyro.x;
        offsetGyroY += g.gyro.y;
        offsetGyroZ += g.gyro.z;
    }

    offsetGyroX /= GYRO_OFFSET_PRECISION;
    offsetGyroY /= GYRO_OFFSET_PRECISION;
    offsetGyroZ /= GYRO_OFFSET_PRECISION;

    Serial.println("");
    delay(100);
}

void mpu_loop()
{

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    counter = (counter + 1) % DATA_SIZE;

    data[counter].accelX = a.acceleration.x;
    data[counter].accelY = a.acceleration.y;
    data[counter].accelZ = a.acceleration.z;
    data[counter].gyroX = g.gyro.x;
    data[counter].gyroY = g.gyro.y;
    data[counter].gyroZ = g.gyro.z;

    float avgAccelX = 0;
    float avgAccelY = 0;
    float avgAccelZ = 0;

    float avgGyroX = 0;
    float avgGyroY = 0;
    float avgGyroZ = 0;

    for (auto j = 0; j < DATA_SIZE; j++)
    {
        avgAccelX += data[j].accelX;
        avgAccelY += data[j].accelY;
        avgAccelZ += data[j].accelZ;

        avgGyroX += data[j].gyroX;
        avgGyroY += data[j].gyroY;
        avgGyroZ += data[j].gyroZ;
    }

    // avgGyroX = ((floor(((avgGyroX / DATA_SIZE) - offsetGyroX) * 100)) / 10000) * 100;
    // avgGyroY = ((floor(((avgGyroY / DATA_SIZE) - offsetGyroY) * 100)) / 10000) * 100;
    // avgGyroZ = ((floor(((avgGyroZ / DATA_SIZE) - offsetGyroZ) * 100)) / 10000) * 100;

    avgGyroX = (avgGyroX / DATA_SIZE) - offsetGyroX;
    avgGyroY = (avgGyroY / DATA_SIZE) - offsetGyroY;
    avgGyroZ = (avgGyroZ / DATA_SIZE) - offsetGyroZ;

    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastTime;

    degrees.x += ((avgGyroX) * (elapsedTime / 1000.0));
    degrees.y += ((avgGyroY) * (elapsedTime / 1000.0));
    degrees.z += ((avgGyroZ) * (elapsedTime / 1000.0));

    lastTime = currentTime;

    delay(1);

    // #ifdef MPU6050_DEBUG
    Serial.print("AccelX:");
    Serial.print(avgAccelX / DATA_SIZE);
    Serial.print(",");
    Serial.print("AccelY:");
    Serial.print(avgAccelY / DATA_SIZE);
    Serial.print(",");
    Serial.print("AccelZ:");
    Serial.print(avgAccelZ / DATA_SIZE);
    Serial.print(", ");
    Serial.print("GyroX:");
    Serial.print(avgGyroX - offsetGyroX, 5);
    Serial.print(",");
    Serial.print("GyroY:");
    Serial.print(avgGyroY - offsetGyroY, 5);
    Serial.print(",");
    Serial.print("GyroZ:");
    Serial.print(avgGyroZ - offsetGyroZ, 5);
    Serial.print(", ");
    Serial.print("DegreesX:");
    Serial.print(degrees.x);
    Serial.print(",");
    Serial.print("DegreesY:");
    Serial.print(degrees.y);
    Serial.print(",");
    Serial.print("DegreesZ:");
    Serial.print(degrees.z);
    Serial.println("");
    // #endif
}