#ifndef COLORED_LOG_PRINTER_H_
#define COLORED_LOG_PRINTER_H_



#include "../oolog.h"



namespace oolog {


class ColoredLogPrinter : public LogPrinter {
    public:
		OOLOG_API ColoredLogPrinter(std::shared_ptr<LogPrinter> origin);
        
		virtual void PrintLog(std::string& textToLog, LogLevel logLevel);
        
    private:
        std::shared_ptr<LogPrinter> originLogPrinter;

		void SetColorAtStart(std::string& textToLog, const LogLevel logLevel);
		void RestoreColorAtEnd(std::string& textToLog);
};



} // namespace oolog

#endif // COLORED_LOG_PRINTER_H_

