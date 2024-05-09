#include "disk.hpp"

constexpr int8_t CS_PIN = D4;

Disk::Disk()
{

    Serial.print("Initializing SD card...");

    Serial.println(sizeof(Disk::WriteData));

    if (!SD.begin(CS_PIN))
    {
        Serial.println("initialization failed!");
        return;
    }

    Serial.println("initialization done.");

    this->file = SD.open("data.dat", FILE_WRITE);

    // IMPLEMENTATION
}

void Disk::save(Disk::WriteData data)
{
    this->counter++;

    file.write((byte *)&data, sizeof(Disk::WriteData));

    if (this->counter % 3 == 0)
    {
        file.flush();
    }
}
