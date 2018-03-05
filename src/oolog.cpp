
#include "../include/oolog.h"


namespace oolog {


    
Log::Log(std::shared_ptr<LogPrinter> logPrinter, LogLevel minLogLevel) :
    printer(std::move(logPrinter)),
    minLevelAllowed(minLogLevel)
{
    // Empty
}



Log::~Log() {
    // Empty
}



void Log::Fatal(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::debug);
}



void Log::Error(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::debug);
}



void Log::Warning(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::debug);
}



void Log::Info(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::debug);
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
            printer.get()->PrintLog(textToLog, logLevel);
	}
}





ConsoleLogPrinter::ConsoleLogPrinter()  {
	// Empty
}



void ConsoleLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
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
    
	std::cout << textToLog;// << std::endl;
}


}


