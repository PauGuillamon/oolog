#ifndef TYPED_LOG_PRINTER_H_
#define TYPED_LOG_PRINTER_H_



#include "../oolog.h"



namespace oolog {


class TypedLogPrinter : public LogPrinter {
    public:
        OOLOG_API TypedLogPrinter(std::shared_ptr<LogPrinter> origin);
        
        virtual void PrintLog(std::string&, LogLevel);

private:
	std::shared_ptr<LogPrinter> originLogPrinter;
};




} // namespace oolog

#endif // TYPED_LOG_PRINTER_H_

