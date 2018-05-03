#ifndef COLORED_LOG_PRINTER_H_
#define COLORED_LOG_PRINTER_H_



#include "../oolog.h"

#if defined _WINDOWS
#include <Windows.h>
#endif


namespace oolog {


class ColoredLogPrinter : public LogPrinter {
    public:
		OOLOG_API ColoredLogPrinter(std::shared_ptr<LogPrinter> origin);
        
		virtual void PrintLog(std::string& textToLog, LogLevel logLevel);
        
    private:
        std::shared_ptr<LogPrinter> originLogPrinter;
#if defined _WINDOWS
		HANDLE consoleHandle;
		CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
#endif

		void SetColor(std::string& textToLog, const LogLevel logLevel);
};



} // namespace oolog

#endif // COLORED_LOG_PRINTER_H_

