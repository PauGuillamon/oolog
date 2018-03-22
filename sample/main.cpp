
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


template<typename T>
bool pair_comparer(T a) {
    std::cout << "pair_comparer single: " << a << std::endl;
    return false;
}

template<typename T>
bool pair_comparer(T a, T b) {
    std::cout << "pair_comparer double: (" << a << ", " << b << ")" << std::endl;
    return a == b;
}

template<typename T, typename... Args>
bool pair_comparer(T a, Args... args) {
    std::cout << "pair_comparer single variadic: (" << a << ")" << std::endl;
    return true;
}

/*template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    return a == b && pair_comparer(args...);
}*/



template<typename T>
void logTemplated(std::ostringstream& str, T t) {
    str << t;
}

template<typename T, typename... Args>
void logTemplated(std::ostringstream& str, T t, Args... args) {
    str << t;
    logTemplated(str, args...);
}


/*
template<typename T, typename... Args>
void LogVariadic(T a, Args... args){
    stream str;
    
    str << a;
    logTemplated(str, args...);
    
    std::string textToLog = str.str();
    printer.get()->PrintLog(textToLog, LogLevel::debug);
}*/
https://eli.thegreenplace.net/2014/variadic-templates-in-c/
https://arne-mertz.de/2016/11/modern-c-features-variadic-templates/
http://en.cppreference.com/w/cpp/language/parameter_pack

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
    
    std::cout << std::endl << std::endl;
    bool compared = pair_comparer(1, 2, 3);
    std:: cout << "compared: " << compared << std::endl;
    
    std::cout << std::endl << std::endl;
    
    compared = pair_comparer(2, 2);
    std:: cout << "compared: " << compared << std::endl;
    
    std::cout << std::endl << std::endl;
    
    //mylogger.LogVariadic(3.5, 2, 3);
    mylogger.LogVariadic(3);
    
    std::ostringstream str;
    str << "Calling function... ";
    logTemplated(str, 123, "inside function. Value: ", 123.5, 5421);
    std::cout << str.str() << std::endl;
    
    return 0;
}

