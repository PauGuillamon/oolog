#ifndef FAKE_PRINTER_H_
#define FAKE_PRINTER_H_



#include "oolog.h"



namespace oolog {
	namespace printers {

		class Fake : public Printer {
			public:
				OOLOG_API Fake();
        
				virtual void PrintLog(std::string& textToLog, LogLevel logLevel);
		};

	}
}

#endif // FAKE_PRINTER_H_

