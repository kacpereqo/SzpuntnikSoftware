#include <cstring>

#include "logger.hpp"

template<typename T>
Logger<T> *Logger<T>::prepareValues(int valuesSize) {
	this->valuesSize = valuesSize;
	*this->values = new T[this->valuesSize];
	*this->valuesTimestamps = new uint32_t[this->valuesSize];
	this->freeValuesIndex = 0;

	return this;
}

template<typename T>
Logger<T> *Logger<T>::wipeValues() {
	this->freeValuesIndex = 0;
	return this;
}

template<typename T>
Logger<T>::Logger(int valuesSize) { this->prepareValues(valuesSize); }

template<typename T>
Logger<T>::~Logger() {
	delete[] (this->values);
	delete[] (this->valuesTimestamps);
}

template<typename T>
Logger<T> *Logger<T>::addToValues(T value, uint32_t timestamp) {
	if (freeValuesIndex >= this->valuesSize) {
		// TODO To decide what to do with overflow
	} else {
		*this->values[this->freeValuesIndex] = value;
		*this->valuesTimestamps[this->freeValuesIndex++] = timestamp;
	}

	return this;
}

template<typename T>
int Logger<T>::getValuesSize() { return this->valuesSize; };

template<typename T>
T **Logger<T>::getFilledValues() {
	T *filledValues[this->freeValuesIndex];
	std::memcpy(filledValues, this->values[0], sizeof(T) * this->freeValuesIndex);

	return filledValues;
}

template<typename T>
int Logger<T>::getFilledValuesSize() { return this->freeValuesIndex; }

template<typename T>
uint32_t **Logger<T>::getFilledValuesTimestamps() {
	uint32_t *filledValuesTimestamps[this->freeValuesIndex];
	std::memcpy(filledValuesTimestamps, this->valuesTimestamps[0], sizeof(uint32_t) * this->freeValuesIndex);

	return filledValuesTimestamps;
}

template<typename T>
LoggerExporter<T> *LoggerExporter<T>::prepareLoggersManaged(int loggersManagedSize) {
	this->loggersManagedSize = loggersManagedSize;
	*this->loggersManaged = new Logger<T> *[this->loggersManagedSize];
	this->loggersManagedSize = 0;

	return this;
}

template<typename T>
LoggerExporter<T> *LoggerExporter<T>::wipeLoggersManagedValues() {
	this->iterateOverLoggersManaged([this](Logger<T> *logger) { logger->wipeValues(); });

	return this;
}

template<typename T>
LoggerExporter<T>::LoggerExporter(int loggersManagedSize) { this->prepareLoggersManaged(loggersManagedSize); }

template<typename T>
LoggerExporter<T> *LoggerExporter<T>::addToLoggersManaged(Logger<T> *logger) {
	if (this->freeLoggersManagedIndex >= this->loggersManagedSize) {
		// TODO To decide what to do with overflow
	} else {
		*this->loggersManaged[this->freeLoggersManagedIndex++] = logger;
	}

	return this;
}

template<typename T>
LoggerExporter<T> *LoggerExporter<T>::iterateOverLoggersManaged(std::function<void(Logger<T> *)> function) {
	for (int i{this->freeLoggersManagedIndex}; i > 0; i--) {
		function(*this->loggersManaged[i]);
	}

	return this;
}