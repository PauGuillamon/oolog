#include "FileLogPrinter.h"


#include <fstream>



namespace oolog {




FileLogPrinter::FileLogPrinter(const std::string logFilename) :
	filename(logFilename)
{
	// Empty
}



void FileLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
	std::ofstream logFile(filename, std::ofstream::app);

	logFile << textToLog;

}


}


