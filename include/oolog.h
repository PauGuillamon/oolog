#ifndef OOLOG_H_
#define OOLOG_H_

#include <functional>
#include <iostream>
namespace oolog {

typedef std::function<std::string(void)> LogFunction;

class iLogger {
	public:
		virtual void PerformLog(LogFunction& logFunction) = 0;
};

enum class LogLevel {
	none,
	fatal,
	error,
	warning,
	info,
	debug,
	verbose
};


class Log : private iLogger {
	public:
		Log(LogLevel minLogLevel) : minLevelAllowed(minLogLevel) { }
		virtual ~Log() { }

		virtual void Debug(LogFunction logFunction) {
			LogIfEnoughLevel(logFunction, LogLevel::debug);
		}

		virtual void Verbose(LogFunction logFunction) {
			LogIfEnoughLevel(logFunction, LogLevel::verbose);
		}
		
	private:
		LogLevel minLevelAllowed;

		void LogIfEnoughLevel(LogFunction& logFunction, LogLevel logLevel) {
			if(logLevel <= minLevelAllowed) {
				PerformLog(logFunction);
			}
		}
};

class ConsoleLog : public Log {
	public:
		ConsoleLog(LogLevel logLevel) : Log(logLevel) { }
	private:
		virtual void PerformLog(std::function<std::string(void)>& logFunction) {
			std::string textToLog = logFunction();
			std::cout << textToLog << std::endl;
		}
};

}

#endif // OOLOG_H_

