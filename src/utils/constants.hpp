#pragma once

#include <cstddef>

constexpr size_t CALIBRATION_SAMPLES = 100;
constexpr size_t CALIBRATION_DELAY = 1;
constexpr size_t MAX_ITERATIONS = 2137;

constexpr float TOOK_OFF_THRESHOLD = 1.5;

constexpr uint32_t TIME_TO_OPEN_PARACHUTE = 5000; // millis
constexpr uint32_t BLOCK_PARACHUTE_TIME = 500;    // millis

constexpr float ALTITUDE_TO_OPEN_PARACHUTE = 250.0f; // meters

constexpr float ROTATION_X_THRESHOLD = 50.0f;