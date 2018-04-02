#include "ColoredLogPrinter.h"



namespace oolog {



ColoredLogPrinter::ColoredLogPrinter(std::shared_ptr<LogPrinter> origin) :
	originLogPrinter(std::move(origin))
{
	// Empty
}



void ColoredLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
	// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
	std::cout << "\033[1;";
	switch (logLevel) {
	case LogLevel::Fatal:
		std::cout << "31m";
		break;

	case LogLevel::Error:
		std::cout << "36m";
		break;

	case LogLevel::Warning:
		std::cout << "35m";
		break;

	case LogLevel::Info:
		std::cout << "34m";
		break;

	case LogLevel::Debug:
		std::cout << "31m";
		break;

	case LogLevel::Verbose:
		std::cout << "30m";
		break;
	}

	originLogPrinter.get()->PrintLog(textToLog, logLevel);
	std::cout << "\033[0m";
}



}


