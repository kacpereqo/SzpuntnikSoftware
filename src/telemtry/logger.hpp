class LoggerExporter;

class Logger {
      private:
	int freeValuesIndex;

	Logger *prepareValues(int valuesSize);

      protected:
	int16_t[] * values;
	int valuesSize;

	friend LoggerExporter::dump();
	Logger *wipeValues();

      public:
	Logger(int valuesSize);

	Logger *addToValues(int16_t value);

	int getValuesSize();
	int getFilledValues();
}

class LoggerExporter {
      protected:
	Logger *[] * loggersManaged;

	LoggerExporter *wipeLoggersManagedValues();

      public:
	LoggerExporter();

	LoggerExporter *addToLoggersManaged(Logger *logger);

	virtual LoggerExporter *dump();
}

class LoggerExporterFlash : public LoggerExporter {
      public:
	LoggerExporterFlash();

	LoggerExporter *dump();
}