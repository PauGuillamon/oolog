#include "printers/decorators/ColorANSI.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			ColorANSI::ColorANSI(std::shared_ptr<Printer> origin) :
				Decorator(std::move(origin))
			{
			}



			void ColorANSI::PrintLog(std::string& textToLog, LogLevel logLevel) {
				SetColor(textToLog, logLevel);
				CallOrigin(textToLog, logLevel);
			}



			void ColorANSI::SetColor(std::string& textToLog, const LogLevel logLevel) {
				logStream stream;
				switch (logLevel) {
				case LogLevel::Fatal:		stream << "\033[1;91m";	break;
				case LogLevel::Error:		stream << "\033[1;91m";	break;
				case LogLevel::Warning:		stream << "\033[1;93m";	break;
				case LogLevel::Info:		stream << "";	break;
				case LogLevel::Debug:		stream << "\033[1;92m";	break;
				case LogLevel::Verbose:		stream << "\033[1;90m";	break;
				default:											break;
				}
				textToLog.insert(0, stream.str());

				// Restores color
				textToLog.append("\033[0m");
			}


		}
	}
}


