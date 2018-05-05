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
			std::ofstream logFile(filename, std::ofstream::app);

			logFile << textToLog;

			logFile.close();
		}

	}
}


