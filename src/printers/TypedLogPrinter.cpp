#include "TypedLogPrinter.h"




namespace oolog {



TypedLogPrinter::TypedLogPrinter(std::shared_ptr<LogPrinter> origin) :
	originLogPrinter(std::move(origin))
{
	// Empty
}



void TypedLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
	logStream stream;
	stream << "[";

	switch (logLevel) {
		case LogLevel::Fatal:	stream << "F";	break;
		case LogLevel::Error:	stream << "E";	break;
		case LogLevel::Warning: stream << "W";	break;
		case LogLevel::Info:	stream << "I";	break;
		case LogLevel::Debug:	stream << "D";	break;
		case LogLevel::Verbose: stream << "V";	break;
		default:				stream << "_";	break;
	}

	stream << "] ";
    
	textToLog.insert(0, stream.str());

	originLogPrinter.get()->PrintLog(textToLog, logLevel);
}


}


