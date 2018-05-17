

#include "printers/RotatedFile.h"



#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Exactly;

using namespace oolog::printers;

class RotatedFileTest : public testing::Test {
	protected:
		virtual void SetUp() {}
		virtual void TearDown() {}
};



class FileManagerFake : public FileManager {
	public:
		MOCK_METHOD1(OpenFileToAppend, std::shared_ptr<FileInterface>(const std::string& fileName));

		MOCK_METHOD1(GetFileSize, unsigned int(const std::string& filename));
		MOCK_METHOD1(FileExists, bool(const std::string& filename));
		MOCK_METHOD1(RemoveFile, void(const std::string& filename));
		MOCK_METHOD2(RenameFile, void(const std::string& currentName, const std::string& newName));
};

class FileAbstractionMock : public FileInterface {
	public:
		FileAbstractionMock(const std::string& filename) : FileInterface(filename) {}

		MOCK_METHOD0(Open, void());
		MOCK_METHOD0(Close, void());
		MOCK_METHOD1(Write, void(const std::string& content));
};

class FileAbstractionFake : public FileInterface {
	public:
		FileAbstractionFake(const std::string& filename) : FileInterface(filename) {}

		virtual void Open() override {}
		virtual void Close() override {}
		virtual void Write(const std::string& content) override {}
};



TEST_F(RotatedFileTest, Test_CheckFileIsOppenedWrittenAndClosed) {
	auto fileAbstraction = std::make_shared<FileAbstractionFake>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 4, fileManager);

	EXPECT_CALL(*fileManager, OpenFileToAppend(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(0));
	EXPECT_CALL(*fileManager, RemoveFile(_)).Times(Exactly(0));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}



TEST_F(RotatedFileTest, Test_CheckZZZZZZZZZZ) {
	auto fileAbstraction = std::make_shared<FileAbstractionMock>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 4, fileManager);

	EXPECT_CALL(*fileManager, OpenFileToAppend(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(0));
	EXPECT_CALL(*fileManager, RemoveFile(_)).Times(Exactly(0));

	EXPECT_CALL(*fileAbstraction, Close()).Times(Exactly(1));
	EXPECT_CALL(*fileAbstraction, Write(_)).Times(Exactly(1));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}

