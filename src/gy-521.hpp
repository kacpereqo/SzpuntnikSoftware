#pragma once

// uncomment for debugging
#define GY_521_DEBUG

constexpr unsigned short GY_521_INIT_PRECISION = 100;
constexpr unsigned short DATA_SIZE = 20;

constexpr short ACTIVATE_ANGLE = 40;

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
