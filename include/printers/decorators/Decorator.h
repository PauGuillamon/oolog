#ifndef OOLOG_PRINTERS_DECORATORS_H_
#define OOLOG_PRINTERS_DECORATORS_H_


#include "oolog.h"
#include "printers/Printer.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			class Decorator : public Printer {
				public:
					OOLOG_API Decorator(std::shared_ptr<Printer> origin);

					virtual void PrintLog(std::string&, LogLevel) = 0;

				protected:
					void CallOrigin(std::string&, LogLevel);

				private:
					std::shared_ptr<Printer> originLogPrinter;
			};

		}
	}
}

#endif // OOLOG_PRINTERS_DECORATORS_H_

