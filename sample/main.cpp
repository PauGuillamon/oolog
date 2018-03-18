
#include "../include/oolog.h"

#include <iostream>
#include <sstream>

void ComplexOperation(oolog::Log& myLog) {
    myLog.Debug([](oolog::out log){ log << "Starting Complex Operation------------"; });
    myLog.Verbose([](oolog::out log){ log << "preparing values...."; });
    myLog.Info([](oolog::out log){ log << "Starting"; });
    myLog.Warning([](oolog::out log){ log << "Some values are out of bound."; });
    myLog.Error([](oolog::out log){ log << "Complex operation detected error: " << 3; });
    myLog.Fatal([](oolog::out log){ log << "Couldn't recover after error. Cancelling operation"; });
    myLog.Info([](oolog::out log){ log << "Operation failed"; });
    myLog.Verbose([](oolog::out log){ log << "preparing to exit"; });
    myLog.Debug([](oolog::out log){ log << "Exiting complex Operation------------"; });
}





int main(){
    std::shared_ptr<oolog::LogPrinter> logPrinter = 
        std::make_shared<oolog::EndlLogPrinter>(
        std::make_shared<oolog::ColoredLogPrinter>(
        std::make_shared<oolog::ConsoleLogPrinter>()));
    
    oolog::Log mylogger(logPrinter, oolog::LogLevel::verbose);

    mylogger.Info([](oolog::out log){ log << "App has started!"; });
    mylogger.Verbose([](oolog::out log){ log << "hello world from oolog!"; });

    ComplexOperation(mylogger);

    
    mylogger.Info([](oolog::out log){ log << "Closing app..."; });
    return 0;
}

