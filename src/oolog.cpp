
#include "oolog.h"

#include <stdexcept>


namespace oolog {


    
Log::Log(std::shared_ptr<printers::Printer> logPrinter, LogLevel maxLogLevel) :
    printer(std::move(logPrinter)),
    maxLevelAllowed(maxLogLevel),
	debugAllowed(false)
{
	if (maxLogLevel == LogLevel::Debug) {
		const std::string errorMessage = "oolog doesn't accept oolog::LogLevel::Debug as initialization level. "
											 "Use oolog::Log::EnableDebug() to allow debug logs.";
		std::cerr << errorMessage << std::endl;
		throw std::runtime_error(errorMessage);
	}
}



void Log::SetLogLevel(LogLevel newLogLevel) {
	std::lock_guard<std::mutex> lock(logMutex);

	maxLevelAllowed = newLogLevel;
}



void Log::EnableDebug() {
    std::lock_guard<std::mutex> lock(logMutex);

	debugAllowed = true;
}



void Log::PrintLog(const logStream& stream, LogLevel logLevel) {
    std::lock_guard<std::mutex> lock(logMutex);

    std::string textToLog = stream.str();
    printer->PrintLog(textToLog, logLevel);
}



bool Log::LogLevelIsAllowed(LogLevel logLevel) {
    std::lock_guard<std::mutex> lock(logMutex);

	bool isAllowed = (logLevel == LogLevel::Debug) ?
										debugAllowed :
										(logLevel <= maxLevelAllowed);
	return isAllowed;
}




}


