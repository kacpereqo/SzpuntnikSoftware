#include "logger.hpp"

Logger::prepareValues(int valuesSize) {
	this->valuesSize{valuesSize};
	this->values = int16_t[this->valuesSize];
	this->freeValuesIndex{0};

	return this;
}

Logger *Logger::wipeValues() {
	this->freeValuesIndex = 0;
	return this;
}

Logger::Logger(int valuesSize) { this->prepareValues(valuesSize); }

Logger *Logger::addToValues(int16_t value) {
	if (freeValuesIndex >= this->valuesSize) {
		// TODO To decide what to do with overflow
	} else {
		this->values[this->freeValuesIndex++] = value;
	}

	return this;
}

int Logger::getValuesSize() { return this->valuesSize; };

int16_t *[] Logger::getFilledValues() {
	int16_t[this->freeValuesIndex] filledValues;
	std::copy(this->values, this->values + this->freeValuesIndex, filledValues);

	return filledValues;
}

int Logger::getFilledValuesSize() {
	return this->freeValuesIndex;
}

LoggerExporter *LoggerExporter::prepareLoggersManaged(int loggersManagedSize) {
	this->loggersManagedSize{loggersManagedSize};
	this->loggersManaged = Logger * [this->loggersManagedSize];
	this->loggersManagedSize{0};

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
		this->loggersManaged[this->freeLoggersManagedIndex++] = logger;
	}

	return this;
}

LoggerExporter *LoggerExporter::iterateOverLoggersManaged(std::function<void(Logger *)> function) {
	for (int i{this->freeLoggersManagedIndex}; i > 0; i--) {
		function(this->loggersManaged[i]);
	}

	return this;
}

LoggerExporterFlash::LoggerExporterFlash(int loggersManagedSize) : LoggerExporter(loggersManagedSize) {}

LoggerExporter *LoggerExporterFlash::dump() {
    
}