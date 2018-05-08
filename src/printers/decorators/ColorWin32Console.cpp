#include "printers/decorators/ColorWin32Console.h"



namespace oolog {
	namespace printers {
		namespace decorators {

			ColorWin32Console::ColorWin32Console(std::shared_ptr<Printer> origin) :
				Decorator(std::move(origin))
			{
				consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			}



			void ColorWin32Console::PrintLog(std::string& textToLog, LogLevel logLevel) {
				SetColor(textToLog, logLevel);
				CallOrigin(textToLog, logLevel);

				SetConsoleColor(consoleScreenBufferInfo.wAttributes);
			}



			void ColorWin32Console::SetColor(std::string& textToLog, const LogLevel logLevel) {
				GetConsoleScreenBufferInfo(consoleHandle, &consoleScreenBufferInfo);

				switch (logLevel) {
					case LogLevel::Fatal:
						SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
						break;

					case LogLevel::Error:
						SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
						break;

					case LogLevel::Warning:
						SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						break;

					case LogLevel::Info:
						SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						break;

					case LogLevel::Debug:
						SetConsoleColor(FOREGROUND_GREEN);
						break;

					case LogLevel::Verbose:
						SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						break;

					default:
						break;
				}
			}



			void ColorWin32Console::SetConsoleColor(WORD attributes) {
				SetConsoleTextAttribute(consoleHandle, attributes);
			}


		}
	}
}


