#include "ColoredLogPrinter.h"



namespace oolog {



ColoredLogPrinter::ColoredLogPrinter(std::shared_ptr<LogPrinter> origin) :
	originLogPrinter(std::move(origin))
{
#if defined _WINDOWS
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}



void ColoredLogPrinter::PrintLog(std::string& textToLog, LogLevel logLevel) {
	SetColor(textToLog, logLevel);

	originLogPrinter.get()->PrintLog(textToLog, logLevel);

#if defined _WINDOWS
	SetConsoleTextAttribute(consoleHandle, consoleScreenBufferInfo.wAttributes);
#endif
}



void ColoredLogPrinter::SetColor(std::string& textToLog, const LogLevel logLevel) {
#if defined _WINDOWS
	GetConsoleScreenBufferInfo(consoleHandle, &consoleScreenBufferInfo);

	switch (logLevel) {
		case LogLevel::Fatal:	SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);										break;
		case LogLevel::Error:	SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);										break;
		case LogLevel::Warning: SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);					break;
		case LogLevel::Info:	SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);	break;
		case LogLevel::Debug:	SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);															break;
		case LogLevel::Verbose: SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);						break;
		default:																																	break;
	}
#else
	logStream stream;
	stream << "\033[1;";
	switch (logLevel) {
		case LogLevel::Fatal:		stream << "31m";	break;
		case LogLevel::Error:		stream << "31m";	break;
		case LogLevel::Warning:		stream << "33m";	break;
		case LogLevel::Info:		stream << "34m";	break;
		case LogLevel::Debug:		stream << "32m";	break;
		case LogLevel::Verbose:		stream << "30m";	break;
		default:										break;
	}
	textToLog.insert(0, stream.str());

	// Restores color
	textToLog.append("\033[0m");
#endif
}






}


