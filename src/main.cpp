#include "gy-521.hpp"

void setup(void)
{
  Serial.begin(115200);
  mpu_init();
}

void loop()
{
  mpu_loop();
}