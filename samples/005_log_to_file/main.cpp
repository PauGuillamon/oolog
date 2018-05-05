
#include "oolog.h"
#include "printers/File.h"
#include "printers/decorators/NewLine.h"
#include "printers/decorators/Timestamp.h"
#include "printers/decorators/Level.h"



int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::Level>(
        std::make_shared<oolog::printers::decorators::Timestamp>(
        std::make_shared<oolog::printers::decorators::NewLine>(
        std::make_shared<oolog::printers::File>("output.log"))));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	log.Info("Sample 005 - logging to a file ------------------");
	log.Warning("hello file!");
	log.Warning("bye file!");

    return 0;
}

