#ifndef OOLOG_H_
#define OOLOG_H_

#include <functional>
#include <iostream>
#include <memory>

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
		virtual void PerformLog(std::string&, LogLevel) = 0;
};


// TODO: I don't want iLogger to be pulic, but it's needed right to allow Decorator Pattern.
class Log : public iLogger {
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
		virtual void PerformLog(std::string&, LogLevel);
};

class ColoredLog : public Log {
public:
    ColoredLog(std::shared_ptr<Log> origin, LogLevel logLevel)
        : Log(logLevel),
        originLog(std::move(origin))
    {
        // Empty
    }
    
private:
    std::shared_ptr<Log> originLog;
    
    virtual void PerformLog(std::string& textToLog, LogLevel logLevel) {
        std::cout << "\033[1;";
        switch(logLevel) {
            case LogLevel::warning:
                std::cout << "36m";
                break;
                
            case LogLevel::debug:
                std::cout << "33m";
                break;
                
            case LogLevel::verbose:
                std::cout << "34m";
                break;
        }
        originLog.get()->PerformLog(textToLog, logLevel);
        std::cout << "\033[0m";
    }
};


}

#endif // OOLOG_H_

