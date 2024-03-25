#pragma once

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

void mpu_init();
void mpu_loop();

constexpr int8_t DATA_SIZE = 20;
constexpr int16_t GYRO_OFFSET_PRECISION = 10000;

struct Position
{
    float x;
    float y;
    float z;
};

struct SensorData
{
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
};
