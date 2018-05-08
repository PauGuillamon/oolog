#include "printers/RotatedFileWithHistory.h"


#include <fstream>



namespace oolog {
	namespace printers {

		RotatedFileWithHistory::RotatedFileWithHistory(const std::string logFilename,
														unsigned long maxSizeInBytes) :
			RotatedFile(logFilename, maxSizeInBytes)
		{
			// Empty
		}



		void RotatedFileWithHistory::RotateFile(const std::string& fileName) {
			// TODO: history level
			std::string newFilename = fileName;
			newFilename += ".1";
			std::rename(fileName.c_str(), newFilename.c_str());
		}

	}
}


