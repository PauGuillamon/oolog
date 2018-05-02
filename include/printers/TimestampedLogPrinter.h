#ifndef TIMESTAMPED_LOG_PRINTER_H_
#define TIMESTAMPED_LOG_PRINTER_H_



#include "../oolog.h"



namespace oolog {


class TimestampedLogPrinter : public LogPrinter {
    public:
        OOLOG_API TimestampedLogPrinter(std::shared_ptr<LogPrinter> origin);
        
        virtual void PrintLog(std::string&, LogLevel);

private:
	std::shared_ptr<LogPrinter> originLogPrinter;

    std::string GetTimestamp();
};




} // namespace oolog

#endif // TIMESTAMPED_LOG_PRINTER_H_

