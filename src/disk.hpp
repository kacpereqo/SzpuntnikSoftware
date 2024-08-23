#include "vec.hpp"
#include <SD.h>
#include <SPI.h>
#include "recovery.hpp"
#include "utils/constants.hpp"

struct DiskData
{
  Vec3<float> acc;
  Vec3<float> gyro;
  Vec3<float> mag;
  Vec3<float> rotation;
  float altitude;
  float pressure_1;
  float pressure_2;
  time_t timestamp;
};

struct Disk
{
private:
  DiskData buffer[BUFFER_SIZE];
  uint64_t saveCounter = 0;
  File file;

public:
  Disk()
  {
    if (!SD.begin(SDCARD_PIN))
    {
      Serial.println("initialization failed!");
      while (1)
        ;
    }
    Serial.println("initialization done.");

    this->file = SD.open("data.bin", FILE_WRITE);
    if (!file)
    {
      Serial.println("error opening file");
    }
  }

  void save(DiskData &data)
  {
    data.timestamp = millis();
    this->buffer[this->saveCounter % BUFFER_SIZE] = data;
    this->saveCounter++;

    if (this->file)
    {
      if (this->saveCounter % 10 == 0)
      {

        file.write((uint8_t *)&buffer, sizeof(DiskData) * BUFFER_SIZE);
        this->file.flush();
      }
    }
    else
    {
      Serial.println("error opening file");
    }
  }

  void save(Recovery::TriggeredBy trigger)
  {
    File recoveryFile = SD.open("recovery.bin", FILE_WRITE);
    if (recoveryFile)
    {
      recoveryFile.write((uint8_t *)&trigger, sizeof(Recovery::TriggeredBy));
      recoveryFile.flush();
      recoveryFile.close();
    }
    else
    {
      Serial.println("error opening file");
    }
  }

  // DiskData &read()
  // {
  //   static DiskData data;
  //   File file = SD.open("data.bin", FILE_READ);

  //   if (file)
  //   {
  //     Serial.println("reading");
  //     while (file.available())
  //     {
  //       file.read((uint8_t *)&data, sizeof(DiskData));
  //       Serial.println(data.timestamp);
  //     }
  //     Serial.println("closing");
  //     delay(10000);
  //     file.close();
  //   }
  //   else
  //   {
  //     Serial.println("error opening file");
  //   }
  //   return data;
  // }
};
