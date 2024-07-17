#ifndef LOGGERFLASH_HPP
#define LOGGERFLASH_HPP

#include <SPI.h>
#include <SD.h>

#include "logger.hpp"

template<typename T>
class LoggerExporterFlash : public LoggerExporter<T> {
      public:
	LoggerExporterFlash(int loggersManagedSize);

	LoggerExporter<T> *dump();
};

#endif