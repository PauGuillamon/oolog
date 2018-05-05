#include "printers/decorators/NewLine.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			NewLine::NewLine(std::shared_ptr<Printer> origin) :
				Decorator(std::move(origin))
			{
				// Empty
			}



			void NewLine::PrintLog(std::string& textToLog, LogLevel logLevel) {
				logStream stream;
				stream << std::endl;
				textToLog.append(stream.str());

				CallOrigin(textToLog, logLevel);
			}

		}
	}
}


