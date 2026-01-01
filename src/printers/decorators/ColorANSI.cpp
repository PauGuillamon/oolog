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
				case LogLevel::Fatal:		stream << "\033[1;31m";	break;
				case LogLevel::Error:		stream << "\033[1;31m";	break;
				case LogLevel::Warning:		stream << "\033[1;33m";	break;
				case LogLevel::Info:		stream << "\033[1;34m";	break;
				case LogLevel::Debug:		stream << "\033[1;32m";	break;
				case LogLevel::Verbose:		stream << "";			break;
				default:											break;
				}
				textToLog.insert(0, stream.str());

				// Restores color
				textToLog.append("\033[0m");
			}


		}
	}
}


