#include "printers/decorators/Level.h"




namespace oolog {
	namespace printers {
		namespace decorators {

			Level::Level(std::shared_ptr<Printer> origin) :
				Decorator(std::move(origin))
			{
				// Empty
			}



			void Level::PrintLog(std::string& textToLog, LogLevel logLevel) {
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

				CallOrigin(textToLog, logLevel);
			}

		}
	}
}


