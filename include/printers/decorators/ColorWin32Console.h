#ifndef COLORWIN32CONSOLE_PRINTER_DECORATOR_H_
#define COLORWIN32CONSOLE_PRINTER_DECORATOR_H_



#include "oolog.h"
#include "printers/decorators/Decorator.h"

#include <Windows.h>


namespace oolog {
	namespace printers {
		namespace decorators {

			class ColorWin32Console : public Decorator {
				public:
					OOLOG_API ColorWin32Console(std::shared_ptr<Printer> origin);
        
					virtual void PrintLog(std::string&, LogLevel) override;
        
				private:
					HANDLE consoleHandle;
					CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;

					void SetColor(std::string& textToLog, const LogLevel logLevel);
					void SetConsoleColor(WORD attributes);
			};

		}
	}
}

#endif // COLORWIN32CONSOLE_PRINTER_DECORATOR_H_

