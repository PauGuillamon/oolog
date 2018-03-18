
#include "../include/oolog.h"

#include <sstream>



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
	LogIfEnoughLevel(logFunction, LogLevel::fatal);
}



void Log::Error(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::error);
}



void Log::Warning(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::warning);
}



void Log::Info(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::info);
}



void Log::Debug(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::debug);
}



void Log::Verbose(LogFunction logFunction) {
	LogIfEnoughLevel(logFunction, LogLevel::verbose);
}



void Log::LogIfEnoughLevel(LogFunction& logFunction, LogLevel logLevel) {
	if(logLevel <= minLevelAllowed) {
            stream str;
            logFunction(str);
            std::string textToLog = str.str();
            printer.get()->PrintLog(textToLog, logLevel);
	}
}





ConsoleLogPrinter::ConsoleLogPrinter()  {
	// Empty
}



void ConsoleLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
    switch(logLevel) {
        case LogLevel::fatal:
            std::cout << "F: ";
            break;
            
        case LogLevel::error:
            std::cout << "E: ";
            break;
            
        case LogLevel::warning:
            std::cout << "W: ";
            break;
            
        case LogLevel::info:
            std::cout << "I: ";
            break;
            
        case LogLevel::debug:
            std::cout << "D: ";
            break;
            
        case LogLevel::verbose:
            std::cout << "V: ";
            break;
            
        default:
            std::cout << "[not implemente in ConsoleLogPrinter]:";
            break;
    }
    
	std::cout << textToLog;// << std::endl;
}


}


