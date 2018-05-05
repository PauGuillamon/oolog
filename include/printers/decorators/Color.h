#ifndef COLOR_PRINTER_DECORATOR_H_
#define COLOR_PRINTER_DECORATOR_H_



#include "oolog.h"
#include "printers/decorators/Decorator.h"

#if defined _WINDOWS
#include <Windows.h>
#endif


namespace oolog {
	namespace printers {
		namespace decorators {

			class Color : public Decorator {
				public:
					OOLOG_API Color(std::shared_ptr<Printer> origin);
        
					virtual void PrintLog(std::string&, LogLevel) override;
        
				private:
			#if defined _WINDOWS
					HANDLE consoleHandle;
					CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
			#endif

					void SetColor(std::string& textToLog, const LogLevel logLevel);
			};

		}
	}
}

#endif // COLOR_PRINTER_DECORATOR_H_

