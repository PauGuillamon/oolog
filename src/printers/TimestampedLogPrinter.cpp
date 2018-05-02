#include "TimestampedLogPrinter.h"


#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>


namespace oolog {




TimestampedLogPrinter::TimestampedLogPrinter(std::shared_ptr<LogPrinter> origin) :
	originLogPrinter(std::move(origin))
{
	// Empty
}



void TimestampedLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
	logStream stream;

	std::string timestamp = GetTimestamp();
	stream << timestamp;

	stream << " ";
    
	textToLog.insert(0, stream.str());

	originLogPrinter.get()->PrintLog(textToLog, logLevel);
}



std::string TimestampedLogPrinter::GetTimestamp() {
	auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);
        
        logStream stream;
        stream << std::put_time(std::localtime(&time), "%Y/%m/%d %H:%M:%S");
        return stream.str();
}


}


