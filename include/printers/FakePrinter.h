#ifndef FAKE_PRINTER_H_
#define FAKE_PRINTER_H_



#include "../oolog.h"



namespace oolog {



class FakePrinter : public LogPrinter {
    public:
		FakePrinter();
        
		virtual void PrintLog(std::string& textToLog, LogLevel logLevel);
};






} // namespace oolog

#endif // FAKE_PRINTER_H_

