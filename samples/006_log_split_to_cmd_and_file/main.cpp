
#include "oolog.h"
#include "printers/Console.h"
#include "printers/File.h"
#include "printers/decorators/Level.h"
#include "printers/decorators/NewLine.h"
#include "printers/decorators/Split.h"
#include "printers/decorators/Timestamp.h"



int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::Level>(
        std::make_shared<oolog::printers::decorators::Timestamp>(
        std::make_shared<oolog::printers::decorators::NewLine>(
        std::make_shared<oolog::printers::decorators::Split>(
			std::make_shared<oolog::printers::Console>(),
			std::make_shared<oolog::printers::File>("output_sample_006.log"))
		)));

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	log.Info("Sample 006 - logging both to console and to a file ------------------");
	log.Warning("hello split log!");
	log.Warning("bye split log!");

    return 0;
}

