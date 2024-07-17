#ifndef LOGGERFLASH_HPP
#define LOGGERFLASH_HPP

#include <SPI.h>
#include <SD.h>

#include "logger.hpp"

class LoggerExporterFlash : public LoggerExporter {
      public:
	LoggerExporterFlash(int loggersManagedSize);

	LoggerExporter *dump();
}

#endif