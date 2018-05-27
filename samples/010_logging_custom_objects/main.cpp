
#include "oolog.h"
#include "printers/Console.h"
#include "printers/decorators/NewLine.h"


class Foo {
	public:
		Foo(int valueX, int valueY) : x(valueX), y(valueY) { }

	private:
		int x;
		int y;

		friend std::ostream &operator<<(std::ostream &os, Foo const &foo);
};



std::ostream &operator<<(std::ostream &os, Foo const &foo) {
	os << "x:" << foo.x << " y:" << foo.y;
	return os;
}



int main(){
    std::shared_ptr<oolog::printers::Printer> logPrinter =
        std::make_shared<oolog::printers::decorators::NewLine>(
		std::make_shared<oolog::printers::Console>());

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

	log.Info("Sample 010 - Logging custom objects");

	Foo bar(1, 2);
	log.Info("bar ", bar);

    return 0;
}

