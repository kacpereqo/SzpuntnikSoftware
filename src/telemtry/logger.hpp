#ifndef LOGGER_H
#define LOGGER_H

#include <functional>
#include <stdint.h>

template<class T>
class Logger;

template<class T>
class LoggerExporter {
      protected:
	Logger<T> ***loggersManaged;
	int loggersManagedSize;
	int freeLoggersManagedIndex;

	LoggerExporter *prepareLoggersManaged(int loggersManagedSize);

	LoggerExporter *wipeLoggersManagedValues();

	LoggerExporter *iterateOverLoggersManaged(std::function<void(Logger<T> *)> function);

      public:
	LoggerExporter(int loggersManagedSize);
	~LoggerExporter();

	LoggerExporter *addToLoggersManaged(Logger<T> *logger);

	virtual LoggerExporter *dump();
};

template<class T>
class Logger {
	Logger<T> *prepareValues(int valuesSize);

      protected:
	T **values;
	uint32_t **valuesTimestamps;

	int valuesSize;
	int freeValuesIndex;

	friend LoggerExporter<T>;
	Logger<T> *wipeValues();

      public:
	Logger(int valuesSize);
	~Logger();

	Logger<T> *addToValues(T value, uint32_t timestamp);

	int getValuesSize();

	T **getFilledValues();
	uint32_t **getFilledValuesTimestamps();
	int getFilledValuesSize();
};

#endif