
#include "oolog.h"
#include "printers/RotatedFileWithHistory.h"
#include "printers/decorators/Level.h"
#include "printers/decorators/NewLine.h"
#include "printers/decorators/Timestamp.h"



int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::Level>(
        std::make_shared<oolog::printers::decorators::Timestamp>(
        std::make_shared<oolog::printers::decorators::NewLine>(
		std::make_shared<oolog::printers::RotatedFileWithHistory>("output_sample_008.log", 20, 3))));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	log.Info("Sample 008 - logging to a file that will be rotated with history ------------------");
	for(int i = 0; i < 10; i++) {
		log.Info(i, " meh");
	}
	log.Warning("bye split log!");

    return 0;
}

