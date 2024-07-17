#include "loggerFlash.hpp"

template<typename T>
LoggerExporterFlash<T>::LoggerExporterFlash(int loggersManagedSize) : LoggerExporter<T>(loggersManagedSize) {}

template<typename T>
LoggerExporter<T> *LoggerExporterFlash<T>::dump() { return this; }
