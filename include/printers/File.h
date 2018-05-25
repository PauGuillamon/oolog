#ifndef FILE_PRINTER_H_
#define FILE_PRINTER_H_



#include "oolog.h"



namespace oolog {
	namespace printers {

		class File : public Printer {
			public:
				OOLOG_API File(const std::string logFilename);
        
				virtual void PrintLog(std::string& textToLog, LogLevel logLevel);

			private:
				std::string filename;
		};


	}

}

#endif // FILE_PRINTER_H_

