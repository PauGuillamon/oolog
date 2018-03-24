#ifndef CONSOLE_LOG_PRINTER_H_
#define CONSOLE_LOG_PRINTER_H_



#include "../oolog.h"



namespace oolog {


class ConsoleLogPrinter : public LogPrinter {
    public:
        ConsoleLogPrinter();
    private:
        virtual void PrintLog(std::string&, LogLevel);
};




} // namespace oolog

#endif // CONSOLE_LOG_PRINTER_H_

