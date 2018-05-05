#include "printers/decorators/Decorator.h"



namespace oolog {
	namespace printers {
		namespace decorators {



			Decorator::Decorator(std::shared_ptr<Printer> origin) :
				originLogPrinter(std::move(origin))
			{
				// Empty
			}



			void Decorator::CallOrigin(std::string& textToLog, LogLevel logLevel) {
				originLogPrinter.get()->PrintLog(textToLog, logLevel);
			}


		}

	}

}


