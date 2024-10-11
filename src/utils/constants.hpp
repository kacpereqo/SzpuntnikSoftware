#pragma once

#include <cstddef>
#include <cstdint>
#include <Arduino.h>

// for calibration purposes
constexpr size_t CALIBRATION_SAMPLES = 1;
constexpr size_t CALIBRATION_DELAY = 1;
constexpr size_t MAX_ITERATIONS = 2137;

// path: src/main.cpp
constexpr float LANDING_THRESHOLD = 2;
constexpr float TOOK_OFF_THRESHOLD = 2.5f;
constexpr uint32_t TIME_TO_OPEN_PARACHUTE = 3000;    // millis
constexpr uint32_t BLOCK_PARACHUTE_TIME = 500;       // millis
constexpr float ALTITUDE_TO_OPEN_PARACHUTE = 250.0f; // meters
constexpr float ROTATION_X_THRESHOLD = 50.0f;
constexpr float ROTATION_Y_THRESHOLD = -30.0f;

constexpr uint32_t SPI_FLASH_BLOCK_SIZE = 65536;
constexpr uint8_t SPI_FLASH_CS_PIN = 10;
constexpr uint32_t SPI_FLASH_MEMORY_SIZE = 16777216;
constexpr uint32_t SPI_FLASH_SECTOR_SIZE = 4096;

// path: src/buzzer.hpp
constexpr uint8_t BUZZER_PIN = D5;

// path: src/parachute.hpp
constexpr uint8_t RECOVERY_SERVO_PIN = D6;

// path: src/disk.hpp
constexpr uint8_t SDCARD_PIN = D4;
constexpr size_t BUFFER_SIZE = 10;