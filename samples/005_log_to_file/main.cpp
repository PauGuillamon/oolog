
#include "oolog.h"
#include "printers/FileLogPrinter.h"
#include "printers/EndlLogPrinter.h"
#include "printers/TimestampedLogPrinter.h"
#include "printers/TypedLogPrinter.h"



int main(){
    std::shared_ptr<oolog::LogPrinter> logPrinter =
        std::make_shared<oolog::TypedLogPrinter>(
        std::make_shared<oolog::TimestampedLogPrinter>(
        std::make_shared<oolog::EndlLogPrinter>(
        std::make_shared<oolog::FileLogPrinter>("output.log"))));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	log.Info("Sample 005 - logging to a file ------------------");
	log.Warning("hello file!");
	log.Warning("bye file!");

    return 0;
}

