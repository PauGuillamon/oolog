#ifndef ROTATEDFILE_PRINTER_H_
#define ROTATEDFILE_PRINTER_H_



#include "oolog.h"



namespace oolog {
	namespace printers {

		class FileInterface {
			public:
				FileInterface(const std::string& filename) { }
				virtual ~FileInterface() {}

				virtual void Open() = 0;
				virtual void Close() = 0;
				virtual void Write(const std::string& content) = 0;

			private:
		};

		class FileManager {
			public:
				virtual ~FileManager() {}

				virtual std::shared_ptr<FileInterface> RetrieveFile(const std::string& fileName);

				virtual unsigned int GetFileSize(const std::string& filename);
				virtual bool FileExists(const std::string& filename);
				virtual void RemoveFile(const std::string& filename);
				virtual void RenameFile(const std::string& currentName, const std::string& newName);
		};



		class RotatedFile : public Printer {
			public:
				OOLOG_API RotatedFile(const std::string logFilename,
									  unsigned long maxSizeInBytes,
									  unsigned char maxHistoryLevels);
				OOLOG_API RotatedFile(const std::string logFilename,
									  unsigned long maxSizeInBytes,
									  unsigned char maxHistoryLevels,
									  std::shared_ptr<FileManager> fileSystem);
				
				virtual void PrintLog(std::string& textToLog, LogLevel logLevel);
			
			private:
				std::string filename;
				unsigned long maxSize;
				unsigned char maxLevels;
				std::shared_ptr<FileManager> fileManager;
			
				void ExecuteRotation(const std::string& fileName);
				bool HasMaxSizeBeenReached(const std::string& fileName);
			
				void RotateFile(const std::string& fileName);
				void RotateToLevel(const std::string& fileName, unsigned char level);
			
				std::string ConstructFilename(const std::string& fileName, unsigned char level);
		};


	}

}

#endif // ROTATEDFILE_PRINTER_H_

