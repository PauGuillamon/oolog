#include "printers/RotatedFile.h"


#include <fstream>



namespace oolog {
	namespace printers {

		class FileAbstraction : public FileInterface {
			public:
				FileAbstraction(const std::string& name) : FileInterface(name), filename(name) { }
				virtual ~FileAbstraction() { }

				virtual void Open() override {
					file.open(filename, std::ofstream::app);
				}
				virtual void Close() override {
					if (file.is_open()) {
						file.close();
					}
				}
				virtual void Write(const std::string& content) override {
					if (file.is_open()) {
						file << content;
					}
				}

			private:
				std::ofstream file;
				std::string filename;
		};

		std::shared_ptr<FileInterface> FileManager::RetrieveFile(const std::string& fileName) {
			auto file = std::make_shared<FileAbstraction>(fileName);
			return file;
		}


		unsigned int FileManager::GetFileSize(const std::string& filename) {
			unsigned long fileSize = 0;

			std::ifstream file(filename, std::ifstream::ate | std::ifstream::binary);
			std::ifstream::pos_type pos = file.tellg();
			if (pos > 0) {
				fileSize = (unsigned long)pos;
			}

			return fileSize;
		}

		bool FileManager::FileExists(const std::string& filename) {
			std::ifstream fileStream(filename.c_str());
			return fileStream.good();
		}

		void FileManager::RemoveFile(const std::string& filename) {
			std::remove(filename.c_str());
		}

		void FileManager::RenameFile(const std::string& currentName, const std::string& newName) {
			std::rename(currentName.c_str(), newName.c_str());
		}



		RotatedFile::RotatedFile(const std::string logFilename,
								unsigned long maxSizeInBytes,
								unsigned char maxHistoryLevels) :
			RotatedFile(logFilename,
						maxSizeInBytes,
						maxHistoryLevels,
						std::make_shared<FileManager>())
		{
			// Empty
		}



		RotatedFile::RotatedFile(const std::string logFilename,
								unsigned long maxSizeInBytes,
								unsigned char maxHistoryLevels,
								std::shared_ptr<FileManager> fileSystem) :
			filename(logFilename),
			maxSize(maxSizeInBytes),
			maxLevels(maxHistoryLevels),
			fileManager(std::move(fileSystem))
		{
			// Empty
		}
		
		
		
		void RotatedFile::PrintLog(std::string& textToLog, LogLevel logLevel) {
			ExecuteRotation(filename);
			
			auto logFile = fileManager->RetrieveFile(filename);
			logFile->Open();
			logFile->Write(textToLog);
			logFile->Close();
		}
		
		
		
		void RotatedFile::ExecuteRotation(const std::string& fileName) {
			if(HasMaxSizeBeenReached(fileName)) {
				RotateFile(fileName);
			}
		}
		
		
		
		bool RotatedFile::HasMaxSizeBeenReached(const std::string& fileName) {
			unsigned long fileSize = fileManager->GetFileSize(fileName);

			bool maxSizeReached = (fileSize >= maxSize);
			
			return maxSizeReached;
		}
		
		
		
		void RotatedFile::RotateFile(const std::string& fileName) {
			if(maxLevels == 0) {
				fileManager->RemoveFile(fileName);
			}
			else {
				RotateToLevel(fileName, 1);
			}
		}
		
		
		
		void RotatedFile::RotateToLevel(const std::string& fileName,
										unsigned char level)
		{
			std::string previousLevelFile = (level == 1) ? 
											fileName :
											ConstructFilename(fileName, level - 1);
			std::string currentLevelFile = ConstructFilename(fileName, level);
			
			if(fileManager->FileExists(currentLevelFile)) {
				if(level == maxLevels) {
					fileManager->RemoveFile(currentLevelFile);
				}
				else if(level < 255) {
					RotateToLevel(fileName, level + 1);
				}
			}

			fileManager->RenameFile(previousLevelFile.c_str(), currentLevelFile.c_str());
		}
		
		
		
		std::string RotatedFile::ConstructFilename(const std::string& fileName,
													unsigned char level)
		{
			std::stringstream stream;
			stream << fileName << "." << int(level);
			return stream.str();
		}

	}
}


