
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
		std::make_shared<oolog::printers::RotatedFile>("output_sample_007.log", 94, 0))));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	log.Info("Sample 007 - logging to a file that will be rotated ------------------");
	log.Info("The previous log won't be in the log after the execution");
	log.Warning("bye rotated log!");

    return 0;
}

