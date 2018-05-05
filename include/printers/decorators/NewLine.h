#ifndef NEWLINE_PRINTER_DECORATOR_H_
#define NEWLINE_PRINTER_DECORATOR_H_



#include "oolog.h"
#include "printers/decorators/Decorator.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			class NewLine : public Decorator {
				public:
					OOLOG_API NewLine(std::shared_ptr<Printer> origin);

					virtual void PrintLog(std::string&, LogLevel) override;

				private:
			};

		}
	}
}

#endif // NEWLINE_PRINTER_DECORATOR_H_

