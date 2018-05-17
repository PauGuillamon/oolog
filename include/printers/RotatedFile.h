#ifndef ROTATEDFILE_PRINTER_H_
#define ROTATEDFILE_PRINTER_H_



#include "oolog.h"



namespace oolog {
	namespace printers {

		class Rotate {
		public:
			Rotate(unsigned char maxHistoryLevels);

		};

		class RotatedFile : public Printer {
			public:
				OOLOG_API RotatedFile(const std::string logFilename,
									  unsigned long maxSizeInBytes,
									  unsigned char maxHistoryLevels);
				
				virtual void PrintLog(std::string& textToLog, LogLevel logLevel);
				
			protected:
				virtual std::ofstream OpenFile(const std::string& fileName);
				virtual void CloseFile(std::ofstream& logFile);
				virtual void WriteToFile(std::ofstream& file, const std::string& content);

				virtual unsigned int GetFileSize(const std::string& filename);
				virtual bool FileExists(const std::string& filename);
				virtual void RemoveFile(const std::string& filename);
				virtual void RenameFile(const std::string& currentName, const std::string& newName);
			
			private:
				std::string filename;
				unsigned long maxSize;
				unsigned char maxLevels;
			
				void ExecuteRotation(const std::string& fileName);
				bool HasMaxSizeBeenReached(const std::string& fileName);
			
				void RotateFile(const std::string& fileName);
				void RotateToLevel(const std::string& fileName, unsigned char level);
			
				std::string ConstructFilename(const std::string& fileName, unsigned char level);
		};


	}

}

#endif // ROTATEDFILE_PRINTER_H_

