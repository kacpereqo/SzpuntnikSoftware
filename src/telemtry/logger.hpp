#ifndef LOGGER_H
#define LOGGER_H

#include <functional>
#include <stdint.h>

class Logger;

class LoggerExporter {
      protected:
	Logger ***loggersManaged;
	int loggersManagedSize;
	int freeLoggersManagedIndex;

	LoggerExporter *prepareLoggersManaged(int loggersManagedSize);

	LoggerExporter *wipeLoggersManagedValues();

	LoggerExporter *iterateOverLoggersManaged(std::function<void(Logger *)> function);

      public:
	LoggerExporter(int loggersManagedSize);
	~LoggerExporter();

	LoggerExporter *addToLoggersManaged(Logger *logger);

	virtual LoggerExporter *dump();
};

class Logger {
	Logger *prepareValues(int valuesSize);

      protected:
	int16_t **values;
	uint32_t **valuesTimestamps;

	int valuesSize;
	int freeValuesIndex;

	friend LoggerExporter;
	Logger *wipeValues();

      public:
	Logger(int valuesSize);
	~Logger();

	Logger *addToValues(int16_t value, uint32_t timestamp);

	int getValuesSize();

	int16_t **getFilledValues();
	uint32_t **getFilledValuesTimestamps();
	int getFilledValuesSize();
};

#endif