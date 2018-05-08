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
				stream << "\033[1;";
				switch (logLevel) {
				case LogLevel::Fatal:		stream << "31m";	break;
				case LogLevel::Error:		stream << "31m";	break;
				case LogLevel::Warning:		stream << "33m";	break;
				case LogLevel::Info:		stream << "34m";	break;
				case LogLevel::Debug:		stream << "32m";	break;
				case LogLevel::Verbose:		stream << "30m";	break;
				default:										break;
				}
				textToLog.insert(0, stream.str());

				// Restores color
				textToLog.append("\033[0m");
			}


		}
	}
}


