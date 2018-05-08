
#include "oolog.h"
#include "printers/Console.h"
#include "printers/decorators/NewLine.h"
#include "printers/decorators/Timestamp.h"
#include "printers/decorators/Level.h"

#include <thread>
#include <chrono>



void ThreadedFunction(oolog::Log* myLog) {
	std::thread::id threadId = std::this_thread::get_id();
	for (int i = 0; i < 10; i++) {
		myLog->Error(i, " - thread id: ", threadId);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}



int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::Level>(
        std::make_shared<oolog::printers::decorators::Timestamp>(
        std::make_shared<oolog::printers::decorators::NewLine>(
        std::make_shared<oolog::printers::Console>())));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	std::thread threadOne(ThreadedFunction, &log);
	std::thread threadTwo(ThreadedFunction, &log);

	threadOne.join();
	threadTwo.join();


    return 0;
}

