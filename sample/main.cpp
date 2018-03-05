
#include "../include/oolog.h"

#include <iostream>


void ComplexOperation(oolog::Log& myLog) {
    myLog.Error([](){ return "Complex operation detected error: "; });
    myLog.Verbose([](){ return "Complex operation competed"; });
}

int main(){
    std::shared_ptr<oolog::LogPrinter> logPrinter = 
        std::make_shared<oolog::EndlLogPrinter>(
        std::make_shared<oolog::ColoredLogPrinter>(
        std::make_shared<oolog::ConsoleLogPrinter>()));
    
    oolog::Log mylogger(logPrinter, oolog::LogLevel::verbose);

    mylogger.Debug([](){ return "App has started!"; });
    mylogger.Verbose([](){ return "hello world from oolog!"; });

    ComplexOperation(mylogger);

    mylogger.Debug([](){return "Closing app..."; });


    return 0;
}

