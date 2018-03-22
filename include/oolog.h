#ifndef OOLOG_H_
#define OOLOG_H_

#include <functional>
#include <sstream>
#include <iostream>
#include <memory>

namespace oolog {

using logStream = std::ostringstream;


enum class LogLevel {
	None,
	Fatal,
	Error,
	Warning,
	Info,
	Debug,
	Verbose
};



class LogPrinter {
	public:
		virtual void PrintLog(std::string&, LogLevel) = 0;
};



class Log {
	public:
		Log(std::shared_ptr<LogPrinter> logPrinter, LogLevel minLogLevel);
		virtual ~Log();

        
        template<typename... Args>
        void Fatal(Args... args) {
            LogIfEnoughLevel(LogLevel::Fatal, args...);
        }
        

        template<typename... Args>
		void Error(Args... args) {
            LogIfEnoughLevel(LogLevel::Error, args...);
        }


        template<typename... Args>
		void Warning(Args... args) {
            LogIfEnoughLevel(LogLevel::Warning, args...);
        }


        template<typename... Args>
		void Info(Args... args) {
            LogIfEnoughLevel(LogLevel::Info, args...);
        }
        

        template<typename... Args>
		void Debug(Args... args) {
            LogIfEnoughLevel(LogLevel::Debug, args...);
        }
        

        template<typename... Args>
		void Verbose(Args... args) {
            LogIfEnoughLevel(LogLevel::Verbose, args...);
        }
                
		
	private:        
        std::shared_ptr<LogPrinter> printer;
		LogLevel minLevelAllowed;

        template<typename T>
        void ExpandLogArgs(logStream& str, const T& t) {
            str << t;
        }

        template<typename T, typename... Args>
        void ExpandLogArgs(logStream& str, T t, const Args&... args) {
            ExpandLogArgs(str, t);
            ExpandLogArgs(str, args...);
        }

        template<typename... Args>
		void LogIfEnoughLevel(LogLevel logLevel, const Args&... args) {
            if(logLevel <= minLevelAllowed) {
                logStream stream;
                ExpandLogArgs(stream, args...);

                PrintLog(stream, logLevel);
            }
        }

        void PrintLog(const logStream& stream, LogLevel logLevel);
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
                case LogLevel::Fatal:
                    std::cout << "31m";
                    break;
                    
                case LogLevel::Error:
                    std::cout << "36m";
                    break;
                    
                case LogLevel::Warning:
                    std::cout << "35m";
                    break;
                    
                case LogLevel::Info:
                    std::cout << "34m";
                    break;
                    
                case LogLevel::Debug:
                    std::cout << "31m";
                    break;
                    
                case LogLevel::Verbose:
                    std::cout << "30m";
                    break;
            }
            
            originLogPrinter.get()->PrintLog(textToLog, logLevel);
            std::cout << "\033[0m";
        }
};



} // namespace oolog

#endif // OOLOG_H_

