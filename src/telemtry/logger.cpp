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
		return this;
	} else {
		this->values[this->freeValuesIndex] = value;
		this->freeValuesIndex++;
	}

	return this;
}

int Logger::getValuesSize() { return this -> getValuesSize };

int Logger::getFilledValues() { return this->freeValuesIndex; }