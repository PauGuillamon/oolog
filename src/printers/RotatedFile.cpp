#include "printers/RotatedFile.h"


#include <fstream>



namespace oolog {
	namespace printers {

		RotatedFile::RotatedFile(const std::string logFilename, unsigned long maxSizeInBytes) :
			File(logFilename),
			maxSize(maxSizeInBytes)
		{
			// Empty
		}



		std::ofstream RotatedFile::OpenFile(const std::string& fileName) {
			if (HasMaxSizeBeenReached(fileName)) {
				RotateFile(fileName);
			}
			return File::OpenFile(fileName);
		}



		void RotatedFile::CloseFile(std::ofstream& logFile) {
			File::CloseFile(logFile);
		}



		void RotatedFile::RotateFile(const std::string& fileName) {
			std::remove(fileName.c_str());
		}



		bool RotatedFile::HasMaxSizeBeenReached(const std::string& fileName) {
			bool maxSizeReached = false;

			std::ifstream file(fileName, std::ifstream::ate | std::ifstream::binary);
			std::ifstream::pos_type pos = file.tellg();

			if (pos > 0) {
				unsigned long fileSize = pos;
				maxSizeReached = (fileSize >= maxSize);
			}

			return maxSizeReached;
		}

	}
}


