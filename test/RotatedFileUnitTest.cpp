

#include "printers/RotatedFile.h"



#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Exactly;

using namespace oolog::printers;

class RotatedFileUnitTest : public testing::Test {
	protected:
		virtual void SetUp() {}
		virtual void TearDown() {}
};



class FileManagerFake : public FileManager {
	public:
		MOCK_METHOD1(RetrieveFile, std::shared_ptr<FileInterface>(const std::string& fileName));

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




TEST_F(RotatedFileUnitTest, File_is_opened_written_and_closed) {
	auto fileAbstraction = std::make_shared<FileAbstractionMock>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 4, fileManager);

	EXPECT_CALL(*fileManager, RetrieveFile(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(0));
	EXPECT_CALL(*fileManager, RemoveFile(_)).Times(Exactly(0));

	EXPECT_CALL(*fileAbstraction, Open()).Times(Exactly(1));
	EXPECT_CALL(*fileAbstraction, Write(_)).Times(Exactly(1));
	EXPECT_CALL(*fileAbstraction, Close()).Times(Exactly(1));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}



TEST_F(RotatedFileUnitTest, File_with_less_size_is_not_rotated) {
	auto fileAbstraction = std::make_shared<FileAbstractionFake>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 4, fileManager);

	EXPECT_CALL(*fileManager, RetrieveFile(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(1023));
	EXPECT_CALL(*fileManager, FileExists("file.log.1")).Times(Exactly(0));
	EXPECT_CALL(*fileManager, RenameFile(_, _)).Times(Exactly(0));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}



TEST_F(RotatedFileUnitTest, File_with_exactly_the_given_size_is_rotated) {
	auto fileAbstraction = std::make_shared<FileAbstractionFake>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 4, fileManager);

	EXPECT_CALL(*fileManager, RetrieveFile(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(1024));
	EXPECT_CALL(*fileManager, FileExists("file.log.1")).Times(Exactly(1)).WillOnce(Return(false));
	EXPECT_CALL(*fileManager, RenameFile("file.log", "file.log.1")).Times(Exactly(1));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}



TEST_F(RotatedFileUnitTest, File_with_more_size_is_rotated) {
	auto fileAbstraction = std::make_shared<FileAbstractionFake>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 4, fileManager);

	EXPECT_CALL(*fileManager, RetrieveFile(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(2048));
	EXPECT_CALL(*fileManager, FileExists("file.log.1")).Times(Exactly(1)).WillOnce(Return(false));
	EXPECT_CALL(*fileManager, RenameFile("file.log", "file.log.1")).Times(Exactly(1));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}



TEST_F(RotatedFileUnitTest, Second_history_level_is_renamed) {
	auto fileAbstraction = std::make_shared<FileAbstractionFake>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 4, fileManager);

	EXPECT_CALL(*fileManager, RetrieveFile(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(1024));
	EXPECT_CALL(*fileManager, FileExists("file.log.1")).Times(Exactly(1)).WillOnce(Return(true));
	EXPECT_CALL(*fileManager, FileExists("file.log.2")).Times(Exactly(1)).WillOnce(Return(false));
	EXPECT_CALL(*fileManager, RenameFile("file.log.1", "file.log.2")).Times(Exactly(1));
	EXPECT_CALL(*fileManager, RenameFile("file.log", "file.log.1")).Times(Exactly(1));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}



TEST_F(RotatedFileUnitTest, Maximum_history_level_is_removed) {
	auto fileAbstraction = std::make_shared<FileAbstractionFake>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 3, fileManager);

	EXPECT_CALL(*fileManager, RetrieveFile(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(1024));
	EXPECT_CALL(*fileManager, FileExists("file.log.1")).Times(Exactly(1)).WillOnce(Return(true));
	EXPECT_CALL(*fileManager, FileExists("file.log.2")).Times(Exactly(1)).WillOnce(Return(true));
	EXPECT_CALL(*fileManager, FileExists("file.log.3")).Times(Exactly(1)).WillOnce(Return(true));

	EXPECT_CALL(*fileManager, RemoveFile("file.log.3")).Times(Exactly(1));
	EXPECT_CALL(*fileManager, RenameFile("file.log.1", "file.log.2")).Times(Exactly(1));
	EXPECT_CALL(*fileManager, RenameFile("file.log.2", "file.log.3")).Times(Exactly(1));
	EXPECT_CALL(*fileManager, RenameFile("file.log", "file.log.1")).Times(Exactly(1));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}



TEST_F(RotatedFileUnitTest, Missing_history_level_stops_rotation) {
	auto fileAbstraction = std::make_shared<FileAbstractionFake>("not_important.log");
	auto fileManager = std::make_shared<FileManagerFake>();
	RotatedFile rotatedFile("file.log", 1024, 3, fileManager);

	EXPECT_CALL(*fileManager, RetrieveFile(_)).WillOnce(Return(fileAbstraction));
	EXPECT_CALL(*fileManager, GetFileSize(_)).WillOnce(Return(1024));
	EXPECT_CALL(*fileManager, FileExists("file.log.1")).Times(Exactly(1)).WillOnce(Return(true));
	EXPECT_CALL(*fileManager, FileExists("file.log.2")).Times(Exactly(1)).WillOnce(Return(false));
	EXPECT_CALL(*fileManager, FileExists("file.log.3")).Times(Exactly(0));

	EXPECT_CALL(*fileManager, RemoveFile("file.log.3")).Times(Exactly(0));
	EXPECT_CALL(*fileManager, RenameFile("file.log.1", "file.log.2")).Times(Exactly(1));
	EXPECT_CALL(*fileManager, RenameFile("file.log.2", "file.log.3")).Times(Exactly(0));
	EXPECT_CALL(*fileManager, RenameFile("file.log", "file.log.1")).Times(Exactly(1));

	std::string textToLog = "text";
	rotatedFile.PrintLog(textToLog, oolog::LogLevel::Info);
}