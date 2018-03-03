#ifndef OOLOG_H_
#define OOLOG_H_

#include <functional>
#include <iostream>
namespace oolog {

typedef std::function<std::string(void)> LogFunction;


enum class LogLevel {
	none,
	fatal,
	error,
	warning,
	info,
	debug,
	verbose
};



class iLogger {
	public:
		virtual void PerformLog(LogFunction&, LogLevel) = 0;
};



class Log : private iLogger {
	public:
		Log(LogLevel minLogLevel);
		virtual ~Log();

		void Fatal(LogFunction);
		void Error(LogFunction);
		void Warning(LogFunction logFunction);
		void Info(LogFunction logFunction);
		void Debug(LogFunction logFunction);
		void Verbose(LogFunction logFunction);
		
	private:
		LogLevel minLevelAllowed;

		void LogIfEnoughLevel(LogFunction& logFunction, LogLevel logLevel);
};

class ConsoleLog : public Log {
	public:
		ConsoleLog(LogLevel logLevel);
	private:
		virtual void PerformLog(LogFunction&, LogLevel);
};

}

#endif // OOLOG_H_

