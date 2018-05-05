#ifndef CONSOLE_PRINTER_H_
#define CONSOLE_PRINTER_H_



#include "oolog.h"



namespace oolog {
	namespace printers {

		class Console : public Printer {
			public:
				OOLOG_API Console();

				virtual void PrintLog(std::string&, LogLevel);
		};


	}
}

#endif // CONSOLE_PRINTER_H_

