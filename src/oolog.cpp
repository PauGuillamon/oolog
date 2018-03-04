
#include "../include/oolog.h"


namespace oolog {


    
Log::Log(LogLevel minLogLevel) : minLevelAllowed(minLogLevel) {
    // Empty
}



Log::~Log() {
    // Empty
}



void Log::Debug(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::debug);
}



void Log::Verbose(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::verbose);
}



void Log::LogIfEnoughLevel(LogFunction& logFunction, LogLevel logLevel) {
	if(logLevel <= minLevelAllowed) {
        std::string textToLog = logFunction();
		PerformLog(textToLog, logLevel);
	}
}





ConsoleLog::ConsoleLog(LogLevel logLevel) : Log(logLevel) {
	// Empty
}



void ConsoleLog::PerformLog(std::string& textToLog, LogLevel logLevel) {
    switch(logLevel) {
        case LogLevel::warning:
            std::cout << "W: ";
            break;
            
        case LogLevel::debug:
            std::cout << "D: ";
            break;
            
        case LogLevel::verbose:
            std::cout << "V: ";
            break;
    }
    
	std::cout << textToLog << std::endl;
}


}


