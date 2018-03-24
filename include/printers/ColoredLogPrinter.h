#ifndef COLORED_LOG_PRINTER_H_
#define COLORED_LOG_PRINTER_H_



#include "../oolog.h"



namespace oolog {


class ColoredLogPrinter : public LogPrinter {
    public:
		ColoredLogPrinter(std::shared_ptr<LogPrinter> origin);
        
    private:
        std::shared_ptr<LogPrinter> originLogPrinter;
        
		virtual void PrintLog(std::string& textToLog, LogLevel logLevel);
};



} // namespace oolog

#endif // COLORED_LOG_PRINTER_H_

