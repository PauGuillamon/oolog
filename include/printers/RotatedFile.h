#ifndef ROTATEDFILE_PRINTER_H_
#define ROTATEDFILE_PRINTER_H_



#include "File.h"



namespace oolog {
	namespace printers {

	class RotatedFile : public File {
		public:
			OOLOG_API RotatedFile(const std::string logFilename,
								  unsigned long maxSizeInBytes,
								  unsigned char maxHistoryLevels);
		
		protected:
			virtual std::ofstream OpenFile(const std::string& fileName) override;
			
		private:
			unsigned long maxSize;
			unsigned char maxLevels;
			
			void ExecuteRotation(const std::string& fileName);
			bool HasMaxSizeBeenReached(const std::string& fileName);
			
			virtual void RotateFile(const std::string& fileName);
			void RotateToLevel(const std::string& fileName, unsigned char level);
			
			std::string ConstructFilename(const std::string& fileName, unsigned char level);
			bool FileExists(const std::string& file);
			void RemoveFile(const std::string& file);
	};


	}

}

#endif // ROTATEDFILE_PRINTER_H_

