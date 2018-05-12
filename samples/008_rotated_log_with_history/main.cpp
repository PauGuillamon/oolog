
#include "oolog.h"
#include "printers/RotatedFile.h"
#include "printers/decorators/Level.h"
#include "printers/decorators/NewLine.h"
#include "printers/decorators/Timestamp.h"



int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::Level>(
        std::make_shared<oolog::printers::decorators::Timestamp>(
        std::make_shared<oolog::printers::decorators::NewLine>(
		std::make_shared<oolog::printers::RotatedFile>("output_sample_008.log", 40, 3))));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	log.Info("Sample 008 - logging to a file that will be rotated with history ------------------");
	int i = 1;
	log.Info(i++, " This log will be lost after rotating the oldest log file");
	log.Info(i++, " This log will end in output_sample_008.log.3");
	log.Info(i++, " This log will end in output_sample_008.log.2");
	log.Info(i++, " This log will end in output_sample_008.log.1");
	log.Info("bye rotated log!");

    return 0;
}

