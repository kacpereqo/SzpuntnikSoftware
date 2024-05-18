#ifndef DISK_HPP
#define DISK_HPP

#include <SD.h>
#include "vec.hpp"

enum class ActivationMethod
{
    manual,
    rotation,
    timer,
};

struct Disk
{
public:
    Disk();

    struct WriteData
    {
        uint32_t timestamp;

        Vec3<int16_t> acceleration;
        Vec3<int16_t> gyro;
        Vec3<int16_t> mag;

        float pressure;
        float temperature;
    };

    // data bytes layout:
    // 0 - 4 : time
    // 5 - 6 : acceleration x
    // 7 - 8 : acceleration y
    // 9 - 10 : acceleration z
    // 11 - 12 : gyro x
    // 13 - 14 : gyro y
    // 15 - 16 : gyro z
    // 17 - 18 : mag x
    // 19 - 20 : mag y
    // 21 - 22 : mag z
    // 23 - 24 : pressure - inner
    // 25 - 26 : pressure - outer
    // 27 - 28 : temperature

    void save(ActivationMethod method);
    void save(Disk::WriteData data);

private:
    File file;
    uint32_t counter = 0;
};

#endif