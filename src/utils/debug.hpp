#pragma once

#include <Arduino.h>

// #define DEBUG

// template <typename T>
// inline void debugPrint(T &msg)
// {
// #ifdef DEBUG
//   Serial.print(msg);
// #else
//   pass
// #endif
// }

// template <typename T>
// inline void debugPrintln(T &msg)
// {
// #ifdef DEBUG
//   Serial.println(msg);
// #else
//   pass
// #endif
// }

void printbuf(const void *buf, uint32_t len)
{
  const uint8_t *p = (const uint8_t *)buf;
  do
  {
    unsigned char b = *p++;
    Serial.print(b >> 4, HEX);
    Serial.print(b & 15, HEX);
    // Serial.printf("%02X", *p++);
    Serial.print(" ");
  } while (--len > 0);
  Serial.println();
}