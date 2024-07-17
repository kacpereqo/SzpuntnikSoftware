#include "loggerFlash.hpp"

template<class T>
LoggerExporterFlash<T>::LoggerExporterFlash(int loggersManagedSize) : LoggerExporter<T>(loggersManagedSize) {}

template<class T>
LoggerExporter<T> *LoggerExporterFlash<T>::dump() { return this; }