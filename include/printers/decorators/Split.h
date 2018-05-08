#ifndef SPLIT_PRINTER_DECORATOR_H_
#define SPLIT_PRINTER_DECORATOR_H_



#include "oolog.h"
#include "printers/decorators/Decorator.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			class Split : public Decorator {
				public:
					OOLOG_API Split(std::shared_ptr<Printer> first, std::shared_ptr<Printer> second);

					virtual void PrintLog(std::string&, LogLevel) override;

			private:
				std::shared_ptr<Printer> originSecond;
			};


		}
	}
}

#endif // SPLIT_PRINTER_DECORATOR_H_

