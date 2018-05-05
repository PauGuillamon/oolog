#ifndef LEVEL_PRINTER_DECORATOR_H_
#define LEVEL_PRINTER_DECORATOR_H_



#include "oolog.h"
#include "printers/decorators/Decorator.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			class Level : public Decorator {
				public:
					OOLOG_API Level(std::shared_ptr<Printer> origin);

					virtual void PrintLog(std::string&, LogLevel) override;
			};


		}
	}
}

#endif // LEVEL_PRINTER_DECORATOR_H_

