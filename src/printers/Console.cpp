#include "printers/Console.h"



namespace oolog {
	namespace printers {

		Console::Console() {
			// Empty
		}



		void Console::PrintLog(std::string& textToLog, LogLevel logLevel) {
			if (logLevel == LogLevel::Error || logLevel == LogLevel::Fatal) {
				std::cerr << textToLog;
			}
			else {
				std::cout << textToLog;
			}
		}

	}
}


