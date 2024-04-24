#ifndef LPS25H_HPP
#define LPS25H_HPP

/*
DATA SHEET:
https://pdf1.alldatasheet.com/datasheet-pdf/view/929259/STMICROELECTRONICS/LPS25H.html
*/

#include <LPS.h>

struct LPS25H
{
    enum class PressureRate : uint8_t
    {
        Hz1,
        Hz7,
        Hz12_5,
        Hz25,
    };
    LPS25H();

        void calibrateBarometer();
    void configureBarometer();
    void configureTemperature();

    float readAlltitude(float pressure);
    float readPressure();
    float readTemperature();

private:
    LPS barometer;

    float startPreassure = 1013.25; // Standard pressure at sea level
};

#endif // LPS25H_HPP