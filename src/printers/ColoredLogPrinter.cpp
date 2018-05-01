#include "ColoredLogPrinter.h"



namespace oolog {



ColoredLogPrinter::ColoredLogPrinter(std::shared_ptr<LogPrinter> origin) :
	originLogPrinter(std::move(origin))
{
	// Empty
}



void ColoredLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
	SetColorAtStart(textToLog, logLevel);
	RestoreColorAtEnd(textToLog);

	originLogPrinter.get()->PrintLog(textToLog, logLevel);
}



void ColoredLogPrinter::SetColorAtStart(std::string& textToLog, const LogLevel logLevel) {
	// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
	
	logStream stream;
	stream << "\033[1;";
	switch (logLevel) {
	case LogLevel::Fatal:
		stream << "31m";
		break;

	case LogLevel::Error:
		stream << "36m";
		break;

	case LogLevel::Warning:
		stream << "35m";
		break;

	case LogLevel::Info:
		stream << "34m";
		break;

	case LogLevel::Debug:
		stream << "31m";
		break;

	case LogLevel::Verbose:
		stream << "30m";
		break;
	}

	textToLog.insert(0, stream.str());
}



void ColoredLogPrinter::RestoreColorAtEnd(std::string& textToLog) {
	textToLog.append("\033[0m");
}



}


