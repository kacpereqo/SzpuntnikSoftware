#include "vec.hpp"
#include <SD.h>
#include <SPI.h>

constexpr uint8_t SDCARD_PIN = D9;

struct Disk
{
private:
  File file;

public:
  Disk()
  {
    if (!SD.begin(7))
    {
      Serial.println("initialization failed!");
      while (1)
        ;
    }
    Serial.println("initialization done.");
  }
  void Save(Vec3<float> &acc, Vec3<float> &gyro, Vec3<float> &mag,
            Vec3<float> &rotation) {}
};
