#ifndef ROTATEDFILEWITHHISTORY_PRINTER_H_
#define ROTATEDFILEWITHHISTORY_PRINTER_H_



#include "RotatedFile.h"



namespace oolog {
	namespace printers {

	class RotatedFileWithHistory : public RotatedFile {
		public:
			OOLOG_API RotatedFileWithHistory(const std::string logFilename, unsigned long maxSizeInBytes);

		protected:
			virtual void RotateFile(const std::string& fileName);
	};


	}

}

#endif // ROTATEDFILEWITHHISTORY_PRINTER_H_

