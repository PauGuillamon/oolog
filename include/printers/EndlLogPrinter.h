#ifndef ENDL_LOG_PRINTER_H_
#define ENDL_LOG_PRINTER_H_



#include "../oolog.h"



namespace oolog {



class EndlLogPrinter : public LogPrinter {
    public:
		OOLOG_API EndlLogPrinter(std::shared_ptr<LogPrinter> origin);
        
		virtual void PrintLog(std::string& textToLog, LogLevel logLevel);

    private:
        std::shared_ptr<LogPrinter> originLogPrinter;
};






} // namespace oolog

#endif // ENDL_LOG_PRINTER_H_

