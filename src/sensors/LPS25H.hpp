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
    void configurePressure();
    void configureTemperature();
    float readAlltitude(float pressure);
    float readPressure();
    float readTemperature();

private:
    LPS ps;
};

#endif // LPS25H_HPP