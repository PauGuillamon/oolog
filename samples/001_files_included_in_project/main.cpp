
#include "oolog.h"
#include "printers/Console.h"
#include "printers/decorators/NewLine.h"



void RunApp(oolog::Log& myLog) {
    myLog.Info("Hello world from oolog!");

    myLog.Verbose("This log won't be printed");
}



int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::NewLine>(
        std::make_shared<oolog::printers::Console>());

    oolog::Log log(logPrinter, oolog::LogLevel::Info);

    RunApp(log);

    return 0;
}

