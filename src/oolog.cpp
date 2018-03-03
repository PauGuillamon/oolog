
#include "../include/oolog.h"


namespace oolog {

Log::Log(LogLevel minLogLevel) : minLevelAllowed(minLogLevel) { }
Log::~Log() { }

void Log::Debug(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::debug);
}

void Log::Verbose(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::verbose);
}
		
void Log::LogIfEnoughLevel(LogFunction& logFunction, LogLevel logLevel) {
	if(logLevel <= minLevelAllowed) {
		PerformLog(logFunction);
	}
}



ConsoleLog::ConsoleLog(LogLevel logLevel) : Log(logLevel) {
	// Empty
}

void ConsoleLog::PerformLog(LogFunction& logFunction, LogLevel logLevel) {
	std::string textToLog = logFunction();
	std::cout << textToLog << std::endl;
}


}


