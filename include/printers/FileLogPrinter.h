#ifndef FILE_LOG_PRINTER_H_
#define FILE_LOG_PRINTER_H_



#include "../oolog.h"



namespace oolog {


class FileLogPrinter : public LogPrinter {
    public:
        OOLOG_API FileLogPrinter(const std::string logFilename);
        
        virtual void PrintLog(std::string&, LogLevel);

	private:
		std::string filename;
};




} // namespace oolog

#endif // FILE_LOG_PRINTER_H_

