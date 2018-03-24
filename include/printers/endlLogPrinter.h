#ifndef ENDL_LOG_PRINTER_H_
#define ENDL_LOG_PRINTER_H_



#include "../oolog.h"



namespace oolog {



class EndlLogPrinter : public LogPrinter {
    public:
		EndlLogPrinter(std::shared_ptr<LogPrinter> origin);

    private:
        std::shared_ptr<LogPrinter> originLogPrinter;
        
		virtual void PrintLog(std::string& textToLog, LogLevel logLevel);
};






} // namespace oolog

#endif // ENDL_LOG_PRINTER_H_

