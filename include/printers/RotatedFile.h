#ifndef ROTATEDFILE_PRINTER_H_
#define ROTATEDFILE_PRINTER_H_



#include "File.h"



namespace oolog {
	namespace printers {

	class RotatedFile : public File {
		public:
			OOLOG_API RotatedFile(const std::string logFilename, unsigned long maxSizeInBytes);

		protected:
			virtual std::ofstream OpenFile(const std::string& fileName) override;
			virtual void CloseFile(std::ofstream& logFile) override;

			virtual void RotateFile(const std::string& fileName);
			virtual bool HasMaxSizeBeenReached(const std::string& fileName);

		private:
			unsigned long maxSize;
	};


	}

}

#endif // ROTATEDFILE_PRINTER_H_

