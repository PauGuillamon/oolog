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



class LogPrinter {
	public:
		virtual void PrintLog(std::string&, LogLevel) = 0;
};



class Log {
	public:
		Log(std::shared_ptr<LogPrinter> logPrinter, LogLevel minLogLevel);
		virtual ~Log();

		void Fatal(LogFunction);
		void Error(LogFunction);
		void Warning(LogFunction logFunction);
		void Info(LogFunction logFunction);
		void Debug(LogFunction logFunction);
		void Verbose(LogFunction logFunction);
		
	private:
                std::shared_ptr<LogPrinter> printer;
		LogLevel minLevelAllowed;

		void LogIfEnoughLevel(LogFunction& logFunction, LogLevel logLevel);
};



class ConsoleLogPrinter : public LogPrinter {
    public:
        ConsoleLogPrinter();
    private:
        virtual void PrintLog(std::string&, LogLevel);
};



class EndlLogPrinter : public LogPrinter {
    public:
        EndlLogPrinter(std::shared_ptr<LogPrinter> origin) : 
            originLogPrinter(std::move(origin))
        {
            // Empty
        }
    private:
        std::shared_ptr<LogPrinter> originLogPrinter;
        
        virtual void PrintLog(std::string& textToLog, LogLevel logLevel) {
            originLogPrinter.get()->PrintLog(textToLog, logLevel);
            std::cout << std::endl;
        }
};



class ColoredLogPrinter : public LogPrinter {
    public:
        ColoredLogPrinter(std::shared_ptr<LogPrinter> origin) : 
            originLogPrinter(std::move(origin))
        {
            // Empty
        }
        
    private:
        std::shared_ptr<LogPrinter> originLogPrinter;
        
        virtual void PrintLog(std::string& textToLog, LogLevel logLevel) {
            // https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
            std::cout << "\033[1;";
            switch(logLevel) {
                case LogLevel::fatal:
                    std::cout << "31m";
                    break;
                    
                case LogLevel::error:
                    std::cout << "36m";
                    break;
                    
                case LogLevel::warning:
                    std::cout << "35m";
                    break;
                    
                case LogLevel::info:
                    std::cout << "34m";
                    break;
                    
                case LogLevel::debug:
                    std::cout << "31m";
                    break;
                    
                case LogLevel::verbose:
                    std::cout << "30m";
                    break;
            }
            
            originLogPrinter.get()->PrintLog(textToLog, logLevel);
            std::cout << "\033[0m";
        }
};



} // namespace oolog

#endif // OOLOG_H_

