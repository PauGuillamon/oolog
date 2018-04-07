#ifndef OOLOG_H_
#define OOLOG_H_



#include <functional>
#include <sstream>
#include <iostream>
#include <memory>



namespace oolog {

using logStream = std::ostringstream;

#ifdef OOLOG_EXPORTS
	#define OOLOG_API __declspec(dllexport)
#else
	#define OOLOG_API
#endif

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
		OOLOG_API Log(std::shared_ptr<LogPrinter> logPrinter, LogLevel minLogLevel);
		OOLOG_API virtual ~Log();


		OOLOG_API void SetLogLevel(LogLevel newLogLevel);

        
        template<typename... Args>
		OOLOG_API void Fatal(Args... args) {
            LogIfEnoughLevel(LogLevel::Fatal, args...);
        }
        

        template<typename... Args>
		OOLOG_API void Error(Args... args) {
            LogIfEnoughLevel(LogLevel::Error, args...);
        }


        template<typename... Args>
		OOLOG_API void Warning(Args... args) {
            LogIfEnoughLevel(LogLevel::Warning, args...);
        }


        template<typename... Args>
		OOLOG_API void Info(Args... args) {
            LogIfEnoughLevel(LogLevel::Info, args...);
        }
        

        template<typename... Args>
		OOLOG_API void Debug(Args... args) {
            LogIfEnoughLevel(LogLevel::Debug, args...);
        }
        

        template<typename... Args>
		OOLOG_API void Verbose(Args... args) {
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
            if(LogLevelIsAllowed(logLevel)) {
                logStream stream;
                ExpandLogArgs(stream, args...);

                PrintLog(stream, logLevel);
            }
        }

		OOLOG_API void PrintLog(const logStream& stream, LogLevel logLevel);
		OOLOG_API bool LogLevelIsAllowed(LogLevel logLevel);
};



} // namespace oolog

#endif // OOLOG_H_

