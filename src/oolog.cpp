
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



void Log::PrintLog(const logStream& stream, LogLevel logLevel) {
    // TODO: thread-safe
    std::string textToLog = stream.str();
    printer->PrintLog(textToLog, logLevel);
}



bool Log::LogLevelIsAllowed(LogLevel logLevel) {
	return (logLevel <= minLevelAllowed);
}




}


