#ifndef COLOR_ANSI_PRINTER_DECORATOR_H_
#define COLOR_ANSI_PRINTER_DECORATOR_H_



#include "oolog.h"
#include "printers/decorators/Decorator.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			class ColorANSI : public Decorator {
				public:
					OOLOG_API ColorANSI(std::shared_ptr<Printer> origin);
        
					virtual void PrintLog(std::string&, LogLevel) override;
        
				private:

					void SetColor(std::string& textToLog, const LogLevel logLevel);
			};

		}
	}
}

#endif // COLOR_ANSI_PRINTER_DECORATOR_H_

