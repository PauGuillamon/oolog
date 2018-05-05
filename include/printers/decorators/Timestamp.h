#ifndef TIMESTAMP_PRINTER_DECORATOR_H_
#define TIMESTAMP_PRINTER_DECORATOR_H_



#include "oolog.h"
#include "printers/decorators/Decorator.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			class Timestamp : public Decorator {
				public:
					OOLOG_API Timestamp(std::shared_ptr<Printer> origin);

					virtual void PrintLog(std::string&, LogLevel) override;

				private:
					std::string GetTimestamp();
			};

		}
	}
}

#endif // TIMESTAMP_PRINTER_DECORATOR_H_

