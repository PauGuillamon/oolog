
#include "oolog.h"
#include "printers/Console.h"
#include "printers/decorators/NewLine.h"


#if defined _WINDOWS
	#if defined _DEBUG
		#define APP_DEBUG
	#endif
#else
	#if !defined _NDEBUG
		#define APP_DEBUG
	#endif
#endif


int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::NewLine>(
		std::make_shared<oolog::printers::Console>());

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);
#if defined APP_DEBUG
	log.EnableDebug();
#endif

	log.Info("Sample 009 - Debug Log");
	log.Debug("This log will only appear when compiling on debug");

    return 0;
}

