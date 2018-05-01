#include "EndlLogPrinter.h"



namespace oolog {



EndlLogPrinter::EndlLogPrinter(std::shared_ptr<LogPrinter> origin) :
	originLogPrinter(std::move(origin))
{
	// Empty
}



void EndlLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
	logStream stream;
	stream << std::endl;
	textToLog.append(stream.str());

	originLogPrinter.get()->PrintLog(textToLog, logLevel);
}



}


