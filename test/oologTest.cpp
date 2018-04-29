

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



TEST_F(LogUnitTest, Test_CheckSameLogLevelIsLogged) {
	std::shared_ptr<MockPrinter> logPrinter = std::make_shared<MockPrinter>();
	oolog::Log log(logPrinter, oolog::LogLevel::Warning);

	EXPECT_CALL(*logPrinter.get(), PrintLog).Times(Exactly(1));

	log.Warning("");
}

