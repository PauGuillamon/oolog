
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



void Log::SetLogLevel(LogLevel newLogLevel) {
	LockMutex();

	minLevelAllowed = newLogLevel;

	UnlockMutex();
}



void Log::PrintLog(const logStream& stream, LogLevel logLevel) {
	LockMutex();

    std::string textToLog = stream.str();
    printer->PrintLog(textToLog, logLevel);

	UnlockMutex();
}



bool Log::LogLevelIsAllowed(LogLevel logLevel) {
	LockMutex();

	bool isAllowed = (logLevel <= minLevelAllowed);

	UnlockMutex();
	return isAllowed;
}



void Log::LockMutex() {
	logMutex.lock();
}



void Log::UnlockMutex() {
	logMutex.unlock();
}




}


