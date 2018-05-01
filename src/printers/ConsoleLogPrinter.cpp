#include "ConsoleLogPrinter.h"


#include <sstream>



namespace oolog {




ConsoleLogPrinter::ConsoleLogPrinter()  {
	// Empty
}



void ConsoleLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
	std::cout << textToLog;
}


}


