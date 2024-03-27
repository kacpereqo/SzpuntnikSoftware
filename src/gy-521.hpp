#pragma once

#define GY_521_DEBUG

constexpr unsigned short GY_521_INIT_PRECISION = 1000;
constexpr unsigned short DATA_SIZE = 25;

struct GY_521
{
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
};

struct Data
{
    float x;
    float y;
    float z;
};

void mpu_init();
void mpu_loop();