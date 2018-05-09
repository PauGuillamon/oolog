#include "printers/RotatedFileWithHistory.h"


#include <fstream>



namespace oolog {
	namespace printers {

		RotatedFileWithHistory::RotatedFileWithHistory(const std::string logFilename,
													   unsigned long maxSizeInBytes,
													   unsigned char maxHistoryLevels) :
			RotatedFile(logFilename, maxSizeInBytes),
			maxLevels(maxHistoryLevels)
		{
			// Empty
		}



		void RotatedFileWithHistory::RotateFile(const std::string& fileName) {
			RotateToLevel(fileName, 1);
		}
		
		
		
		void RotatedFileWithHistory::RotateToLevel(const std::string& fileName,
												   unsigned char level)
		{
			std::string previousLevelFile = (level == 1) ? 
											fileName :
											ConstructFilename(fileName, level - 1);
			std::string currentLevelFile = ConstructFilename(fileName, level);
			
			if(FileExists(currentLevelFile)) {
				if(level == maxLevels) {
					RemoveFile(currentLevelFile);
				}
				else if(level < 255) {
					RotateToLevel(fileName, level + 1);
				}
			}
			
			std::rename(previousLevelFile.c_str(), currentLevelFile.c_str());
		}
		
		
		
		std::string RotatedFileWithHistory::ConstructFilename(const std::string& fileName,
															  unsigned char level)
		{
			std::stringstream stream;
			stream << fileName << "." << int(level);
			return stream.str();
		}
		
		
		
		bool RotatedFileWithHistory::FileExists(const std::string& file) {
			std::ifstream fileStream(file.c_str());
			return fileStream.good();
		}
		
		
		
		void RotatedFileWithHistory::RemoveFile(const std::string& file) {
			std::remove(file.c_str());
		}

	}
}


