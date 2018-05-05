#include "printers/decorators/Timestamp.h"


#include <chrono>
#include <iomanip>


namespace oolog {
	namespace printers {
		namespace decorators {

			Timestamp::Timestamp(std::shared_ptr<Printer> origin) :
				Decorator(std::move(origin))
			{
				// Empty
			}



			void Timestamp::PrintLog(std::string& textToLog, LogLevel logLevel) {
				logStream stream;

				std::string timestamp = GetTimestamp();
				stream << timestamp;
				stream << " ";

				textToLog.insert(0, stream.str());

				CallOrigin(textToLog, logLevel);
			}



			std::string Timestamp::GetTimestamp() {
				auto now = std::chrono::system_clock::now();
				std::time_t time = std::chrono::system_clock::to_time_t(now);

				logStream stream;
				stream << std::put_time(std::localtime(&time), "%Y/%m/%d %H:%M:%S");
				return stream.str();
			}

		}
	}
}


