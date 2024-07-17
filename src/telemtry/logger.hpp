#include <functional>

class LoggerExporter;

class Logger {
	Logger *prepareValues(int valuesSize);

      protected:
	int16_t[] * values;
	int valuesSize;
	int freeValuesIndex;

	friend LoggerExporter::dump();
	Logger *wipeValues();

      public:
	Logger(int valuesSize);

	Logger *addToValues(int16_t value);

	int getValuesSize();

	int16_t *[] getFilledValues();
	int getFilledValuesSize();
}

class LoggerExporter {
      protected:
	Logger *[] * loggersManaged;
	int loggersManagedSize;
	int freeLoggersManagedIndex;

	LoggerExporter *prepareLoggersManaged(int loggersManagedSize);

	LoggerExporter *wipeLoggersManagedValues();

	LoggerExporter *iterateOverLoggersManaged(std::function<void(Logger *)> function);

      public:
	LoggerExporter(int loggersManagedSize);

	LoggerExporter *addToLoggersManaged(Logger *logger);

	virtual LoggerExporter *dump() {};
}

class LoggerExporterFlash : public LoggerExporter {
      public:
	LoggerExporterFlash(int loggersManagedSize);

	LoggerExporter *dump();
}

class LoggerExporterSD : public LoggerExporter {
	// TODO Decide if SD is needed
}