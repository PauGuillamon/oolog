

#include "oolog.h"
#include "printers/Fake.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Exactly;

class LogUnitTest : public testing::Test {
	protected:
		virtual void SetUp() {}
		virtual void TearDown() {}
};



class MockPrinter : public oolog::printers::Fake {
    public:
        MOCK_METHOD2(PrintLog, void(std::string& str, oolog::LogLevel logLevel));
};



TEST_F(LogUnitTest, Same_level_is_logged) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(1));

	log.Warning("");
}



TEST_F(LogUnitTest, Higher_level_is_logged) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(1));

	log.Error("");
}



TEST_F(LogUnitTest, Lower_level_is_not_logged) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(0));

	log.Verbose("");
}



TEST_F(LogUnitTest, Error_is_logged_after_changing_level) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

    log.SetLogLevel(oolog::LogLevel::Error);
	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(1));

	log.Error("");
}



TEST_F(LogUnitTest, Warning_is_not_logged_after_changing_level) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	log.SetLogLevel(oolog::LogLevel::Error);
	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(0));

	log.Warning("");
}



TEST_F(LogUnitTest, Debug_is_not_logged_by_default) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(0));

	log.Debug("");
}



TEST_F(LogUnitTest, Debug_is_logged_if_enabled) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	log.EnableDebug();
	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(1));

	log.Debug("");
}



TEST_F(LogUnitTest, Exception_is_thrown_if_initialized_in_debug_level) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	
	EXPECT_THROW(oolog::Log log(logPrinter, oolog::LogLevel::Debug), std::string);
}

