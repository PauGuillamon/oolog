#ifndef ROTATEDFILEWITHHISTORY_PRINTER_H_
#define ROTATEDFILEWITHHISTORY_PRINTER_H_



#include "RotatedFile.h"



namespace oolog {
	namespace printers {

	class RotatedFileWithHistory : public RotatedFile {
		public:
			OOLOG_API RotatedFileWithHistory(const std::string logFilename,
											 unsigned long maxSizeInBytes,
											 unsigned char maxHistoryLevels);

		protected:
			virtual void RotateFile(const std::string& fileName);
			
		private:
			unsigned char maxLevels;
			
			void RotateToLevel(const std::string& fileName, unsigned char level);
			std::string ConstructFilename(const std::string& fileName, unsigned char level);
			bool FileExists(const std::string& file);
			void RemoveFile(const std::string& file);
	};


	}

}

#endif // ROTATEDFILEWITHHISTORY_PRINTER_H_

