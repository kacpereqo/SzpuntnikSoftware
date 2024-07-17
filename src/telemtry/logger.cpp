#include <cstring>

#include "logger.hpp"

Logger *Logger::prepareValues(int valuesSize) {
	this->valuesSize = valuesSize;
	*this->values = new int16_t[this->valuesSize];
	*this->valuesTimestamps = new uint32_t[this->valuesSize];
	this->freeValuesIndex = 0;

	return this;
}

Logger *Logger::wipeValues() {
	this->freeValuesIndex = 0;
	return this;
}

Logger::Logger(int valuesSize) { this->prepareValues(valuesSize); }

Logger::~Logger() {
	delete[] (this->values);
	delete[] (this->valuesTimestamps);
}

Logger *Logger::addToValues(int16_t value, uint32_t timestamp) {
	if (freeValuesIndex >= this->valuesSize) {
		// TODO To decide what to do with overflow
	} else {
		*this->values[this->freeValuesIndex] = value;
		*this->valuesTimestamps[this->freeValuesIndex++] = timestamp;
	}

	return this;
}

int Logger::getValuesSize() { return this->valuesSize; };

int16_t **Logger::getFilledValues() {
	int16_t *filledValues[this->freeValuesIndex];
	std::memcpy(filledValues, this->values[0], sizeof(int16_t) * this->freeValuesIndex);

	return filledValues;
}

int Logger::getFilledValuesSize() { return this->freeValuesIndex; }

uint32_t **Logger::getFilledValuesTimestamps() {
	uint32_t *filledValuesTimestamps[this->freeValuesIndex];
	std::memcpy(filledValuesTimestamps, this->valuesTimestamps[0], sizeof(uint32_t) * this->freeValuesIndex);

	return filledValuesTimestamps;
}

LoggerExporter *LoggerExporter::prepareLoggersManaged(int loggersManagedSize) {
	this->loggersManagedSize = loggersManagedSize;
	*this->loggersManaged = new Logger *[this->loggersManagedSize];
	this->loggersManagedSize = 0;

	return this;
}

LoggerExporter *LoggerExporter::wipeLoggersManagedValues() {
	this->iterateOverLoggersManaged([this](Logger *logger) { logger->wipeValues(); });

	return this;
}

LoggerExporter::LoggerExporter(int loggersManagedSize) { this->prepareLoggersManaged(loggersManagedSize); }

LoggerExporter *LoggerExporter::addToLoggersManaged(Logger *logger) {
	if (this->freeLoggersManagedIndex >= this->loggersManagedSize) {
		// TODO To decide what to do with overflow
	} else {
		*this->loggersManaged[this->freeLoggersManagedIndex++] = logger;
	}

	return this;
}

LoggerExporter *LoggerExporter::iterateOverLoggersManaged(std::function<void(Logger *)> function) {
	for (int i{this->freeLoggersManagedIndex}; i > 0; i--) {
		function(*this->loggersManaged[i]);
	}

	return this;
}