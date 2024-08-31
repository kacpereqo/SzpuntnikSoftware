#include "flash.hpp"
#include "utils/constants.hpp"
#include "utils/debug.hpp"
#include <Arduino.h>
#include <SerialFlash.h>

// struct DiskData
// {
//     uint32_t a;
//     uint32_t b;
// };

Flash::Flash()
{
    byte idBuffor[3];
    byte data[sizeof(DiskData)];

    SerialFlash.begin(SPI_FLASH_CS_PIN);
    SerialFlash.readID(idBuffor);
    Serial.print("JEDEC ID: ");
    printbuf(idBuffor, 3);

    // find first erased block
    address = 0;

    while (address < SPI_FLASH_MEMORY_SIZE)
    {
        SerialFlash.read(address, data, sizeof(DiskData));
        if (is_erased(data, sizeof(DiskData)))
            break;
        address += sizeof(DiskData);
    }
}

void Flash::write(void *buf)
{
    if (address + sizeof(DiskData) > SPI_FLASH_MEMORY_SIZE)
    {
        Serial.println("Flash memory full");
        return;
    }

    SerialFlash.write(address, buf, sizeof(DiskData));
    address += sizeof(DiskData);
}

bool Flash::is_erased(const unsigned char *data, unsigned int len)
{
    while (len > 0)
    {
        if (*data++ != 255)
            return false;
        len = len - 1;
    }
    return true;
}

void Flash::printAll()
{
    byte data[sizeof(DiskData)];
    uint32_t addr = 0;
    bool first = true;
    while (addr < SPI_FLASH_MEMORY_SIZE / (1024 * 16))
    {
        SerialFlash.read(addr, data, sizeof(DiskData));
        Serial.print("Address: ");
        Serial.print(addr, HEX);
        Serial.print(" Data: ");
        printbuf(data, sizeof(DiskData));

        addr += sizeof(DiskData);
    }
}

void Flash::print(uint32_t endAddress)
{
    byte data[sizeof(DiskData)];
    uint32_t addr = 0;
    bool first = true;
    while (addr < endAddress)
    {
        SerialFlash.read(addr, data, sizeof(DiskData));
        Serial.print("Address: ");
        Serial.print(addr, HEX);
        Serial.print(" Data: ");
        printbuf(data, sizeof(DiskData));

        addr += sizeof(DiskData);
    }
}

void Flash::dumpToSD(Disk &disk)
{
    byte data[sizeof(DiskData)];
    uint32_t addr = 0;
    while (addr < SPI_FLASH_MEMORY_SIZE)
    {
        SerialFlash.read(addr, data, sizeof(DiskData));
        DiskData *diskData = (DiskData *)data;
        disk.save(*diskData);
        addr += sizeof(DiskData);
    }
}

void Flash::eraseAll()
{
    SerialFlash.eraseAll();

    while (SerialFlash.ready() == false)
        ;

    address = 0;
}

void Flash::printHumanReadable()
{
    byte data[sizeof(DiskData)];
    uint32_t addr = 0;
    while (addr < SPI_FLASH_MEMORY_SIZE)
    {
        SerialFlash.read(addr, data, sizeof(DiskData));
        DiskData *diskData = (DiskData *)data;
        Serial.print("Address: ");
        Serial.print(addr, HEX);
        Serial.print(" Data: ");
        Serial.print("Acc: ");
        Serial.print(diskData->acc.x);
        Serial.print(" ");
        Serial.print(diskData->acc.y);
        Serial.print(" ");
        Serial.print(diskData->acc.z);
        Serial.print(" Gyro: ");
        Serial.print(diskData->gyro.x);
        Serial.print(" ");
        Serial.print(diskData->gyro.y);
        Serial.print(" ");
        Serial.print(diskData->gyro.z);
        Serial.print(" Mag: ");
        Serial.print(diskData->mag.x);
        Serial.print(" ");
        Serial.print(diskData->mag.y);
        Serial.print(" ");
        Serial.print(diskData->mag.z);
        Serial.print(" Altitude: ");
        Serial.print(diskData->altitude);
        Serial.print(" Pressure 1: ");
        Serial.print(diskData->pressure_1);
        Serial.print(" Pressure 2: ");
        Serial.print(diskData->pressure_2);
        Serial.print(" Timestamp: ");
        Serial.println(diskData->timestamp);

        addr += sizeof(DiskData);
    }
}