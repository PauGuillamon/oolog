
#include "oolog.h"
#include "printers/ConsoleLogPrinter.h"
#include "printers/EndlLogPrinter.h"



void RunApp(oolog::Log& myLog) {
    myLog.Info("Hello world from oolog!");

    myLog.Verbose("This log won't be printed");
}



int main(){
    std::shared_ptr<oolog::LogPrinter> logPrinter =
        std::make_shared<oolog::EndlLogPrinter>(
        std::make_shared<oolog::ConsoleLogPrinter>());

    oolog::Log log(logPrinter, oolog::LogLevel::Info);

    RunApp(log);

    return 0;
}

