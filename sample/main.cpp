
#include "../include/oolog.h"

#include <iostream>
#include <sstream>

void ComplexOperation(oolog::Log& myLog) {
    myLog.Error([](){ return "Complex operation detected error: "; });
    myLog.Verbose([](){ return "Complex operation competed"; });
}



void TestOstream(std::function<void(std::ostringstream& log)> function){
    std::ostringstream outStream;
    function(outStream);
    std::cout << "OutStream says: \"" << outStream.str() << "\"" << std::endl;
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


    TestOstream([](std::ostringstream& log) {log << "myLog!"; });
    
    return 0;
}

