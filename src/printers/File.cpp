#include "printers/File.h"


#include <fstream>



namespace oolog {
	namespace printers {

		File::File(const std::string logFilename) :
			filename(logFilename)
		{
			// Empty
		}



		void File::PrintLog(std::string& textToLog, LogLevel logLevel) {
			std::ofstream logFile = OpenFile(filename);
			logFile << textToLog;
			CloseFile(logFile);
		}



		std::ofstream File::OpenFile(const std::string& fileName) {
			std::ofstream logFile(fileName, std::ofstream::app);
			return logFile;
		}



		void File::CloseFile(std::ofstream& logFile) {
			logFile.close();
		}

	}
}


