#include "printers/decorators/Split.h"




namespace oolog {
	namespace printers {
		namespace decorators {

			Split::Split(std::shared_ptr<Printer> first, std::shared_ptr<Printer> second) :
				Decorator(std::move(first)),
				originSecond(std::move(second))
			{
				// Empty
			}



			void Split::PrintLog(std::string& textToLog, LogLevel logLevel) {
				CallOrigin(textToLog, logLevel);
				originSecond.get()->PrintLog(textToLog, logLevel);
			}

		}
	}
}


