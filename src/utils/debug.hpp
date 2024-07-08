#pragma once

#include <Arduino.h>

#define DEBUG

template <typename T> inline void debugPrint(T &msg) {
#ifdef DEBUG
  Serial.print(msg);
#else
  pass
#endif
}

template <typename T> inline void debugPrintln(T &msg) {
#ifdef DEBUG
  Serial.println(msg);
#else
  pass
#endif
}