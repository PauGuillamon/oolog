
#include "oolog.h"
#include "printers/ConsoleLogPrinter.h"
#include "printers/ColoredLogPrinter.h"
#include "printers/EndlLogPrinter.h"



void ComplexOperation(oolog::Log& myLog) {
    myLog.Debug("Starting Complex Operation------------");
    myLog.Verbose("preparing values....");
    myLog.Info("Starting");
    myLog.Warning("Some values are out of bound.");
    myLog.Error("Complex operation detected error: ", 3);
    myLog.Fatal("Couldn't recover after error. Cancelling operation");
    myLog.Info("Operation failed");
    myLog.Verbose("preparing to exit");
    myLog.Debug("Exiting complex Operation------------");
}



void RunApp(oolog::Log& myLog) {
    myLog.Info("App has started!");

    myLog.Verbose("hello world from oolog!");

    ComplexOperation(myLog);

    myLog.Info("Closing app...");
}



int main(){
    std::shared_ptr<oolog::LogPrinter> logPrinter =
        std::make_shared<oolog::EndlLogPrinter>(
        std::make_shared<oolog::ColoredLogPrinter>(
        std::make_shared<oolog::ConsoleLogPrinter>()));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

    RunApp(log);

    return 0;
}

