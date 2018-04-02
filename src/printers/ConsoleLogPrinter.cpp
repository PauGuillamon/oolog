#include "ConsoleLogPrinter.h"


#include <sstream>



namespace oolog {




ConsoleLogPrinter::ConsoleLogPrinter()  {
	// Empty
}



void ConsoleLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
    switch(logLevel) {
        case LogLevel::Fatal:
            std::cout << "F: ";
            break;

        case LogLevel::Error:
            std::cout << "E: ";
            break;

        case LogLevel::Warning:
            std::cout << "W: ";
            break;

        case LogLevel::Info:
            std::cout << "I: ";
            break;

        case LogLevel::Debug:
            std::cout << "D: ";
            break;

        case LogLevel::Verbose:
            std::cout << "V: ";
            break;

        default:
            std::cout << "[not implemente in ConsoleLogPrinter]:";
            break;
    }

	std::cout << textToLog;// << std::endl;
}


}


