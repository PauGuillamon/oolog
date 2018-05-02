

#include "oolog.h"
#include "printers/FakePrinter.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Exactly;

class LogUnitTest : public testing::Test {
	protected:
		virtual void SetUp() {}
		virtual void TearDown() {}
};



class MockPrinter : public oolog::FakePrinter {
    public:
        MOCK_METHOD2(PrintLog, void(std::string& str, oolog::LogLevel logLevel));
};



TEST_F(LogUnitTest, Test_CheckSameLevelIsLogged) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(1));

	log.Warning("");
}



TEST_F(LogUnitTest, Test_CheckHigherLevelIsLogged) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(1));

	log.Error("");
}



TEST_F(LogUnitTest, Test_CheckLowerLevelIsNotLogged) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(0));

	log.Verbose("");
}



TEST_F(LogUnitTest, Test_CheckErrorIsLoggedAfterChangingLevel) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

        log.SetLogLevel(oolog::LogLevel::Error);
	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(0));

	log.Error("");
}



TEST_F(LogUnitTest, Test_CheckWarningIsNotLoggedAfterChangingLevel) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

        log.SetLogLevel(oolog::LogLevel::Error);
	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(0));

	log.Warning("");
}

