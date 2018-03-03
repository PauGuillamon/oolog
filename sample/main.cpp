
#include "../include/oolog.h"

#include <iostream>


void ComplexOperation(oolog::Log& myLog) {
	myLog.Verbose([](){ return "Complex operation competed"; });
}

int main(){
	oolog::ConsoleLog mylogger(oolog::LogLevel::verbose);

	mylogger.Debug([](){ return "App has started!"; });
	mylogger.Verbose([](){ return "hello world from oolog!"; });

	ComplexOperation(mylogger);

	mylogger.Debug([](){return "Closing app..."; });

	return 0;
}

