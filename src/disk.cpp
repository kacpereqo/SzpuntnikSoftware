#include "disk.hpp"

constexpr int8_t CS_PIN = D4;

Disk::Disk()
{

    // // Serial.print("Initializing SD card...");

    // // Serial.println(sizeof(Disk::WriteData));

    if (!SD.begin(CS_PIN))
    {
        // // Serial.println("initialization failed!");
        return;
    }

    // // Serial.println("initialization done.");

    this->file = SD.open("data.csv", FILE_WRITE);

    // IMPLEMENTATION
}

void Disk::save(ActivationMethod method)
{
    this->counter++;

    file.write((byte *)&method, sizeof(ActivationMethod));
    file.write('\n');

    if (this->counter % 3 == 0)
    {
        file.flush();
    }
}

void Disk::save(Disk::WriteData data)
{
    this->counter++;

    file.print(data.timestamp);
    file.print(",");
    file.print(data.acceleration.x);
    file.print(",");
    file.print(data.acceleration.y);
    file.print(",");
    file.print(data.acceleration.z);
    file.print(",");
    file.print(data.gyro.x);
    file.print(",");
    file.print(data.gyro.y);
    file.print(",");
    file.print(data.gyro.z);
    file.print(",");
    file.print(data.mag.x);
    file.print(",");
    file.print(data.mag.y);
    file.print(",");
    file.print(data.mag.z);
    file.print(",");
    file.print(data.pressure);
    file.print(",");
    file.print(data.temperature);
    file.print('\n');

    if (this->counter % 3 == 0)
    {
        file.flush();
    }
}
