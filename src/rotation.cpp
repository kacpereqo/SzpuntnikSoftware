#include "rotation.hpp"
#include "macros.h"
#include <Arduino.h>

void Rotation::updateRotation()
{
#ifdef ROTATION_DEBUG
    Serial.print(x);
    Serial.print(",");

    Serial.print(y);
    Serial.print(",");

    Serial.print(z);
    Serial.print(",");

    Serial.println();
#endif
}