#ifndef OOLOG_PRINTERS_H_
#define OOLOG_PRINTERS_H_

#include <string>

namespace oolog {

	enum class LogLevel;

	namespace printers {

		class Printer {
		public:
			virtual void PrintLog(std::string&, LogLevel) = 0;
		};

	}
}

#endif // OOLOG_PRINTERS_H_

