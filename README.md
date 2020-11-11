# oolog
[![Build Status](https://travis-ci.org/PauGuillamon/oolog.svg?branch=master)](https://travis-ci.org/PauGuillamon/oolog)
### Table of contents
- [Overview](#overview)
    - [Why another log library](#why-another-log-library)
    - [Contribute](#contribute)
- [Getting started](#getting-started)
    - [Get the code](#get-the-code)
    - [Quick start](#quick-start)
    - [Log levels](#log-levels)
- [Design](#design)
    - [Log parameters](#log-parameters)
    - [Available Printers](#available-printers)
    - [Available Decorators](#available-decorators)
    - [Testing code using oolog](#testing-code-using-oolog)
- [Understanding Decorators stack](#understanding-decorators-stack)
- [Customization](#customization)
    - [Printers](#printers)
    - [Decorators](#decorators)
- [License](#license)

# Overview
oolog stands for object oriented log. It is a customizable and easy to use logging library  for Modern C++ application.

## Why another log library
The main reason that motivated me to make another log library was the fact that the most famous C++ log libraries on GitHub don't follow some code practices I am very used to.

In this library you won't use magic global initialization macros, there are no global states and you won't need to learn a new way of formatting text.

With this library, you will use proper objects. You will have the ability to create as many log objects as you want and customize them as you like.

Code using this library, will be easy to test and you won't have to worry about test code logging to console or files. You will only need to inject the provided test double to your class under test.

## Contribute
If you find a bug or can think of an improvement, please, feel free to contribute! Open an issue for any questions or doubts you may have (that means the documentation may not be clear enough, and that's a bug!) and feel free to submit pull requests.

# Getting started
## Get the code
```
git clone https://github.com/PauGuillamon/oolog.git
```
Once you have the repository, you can [build it](#build) in order to link against a shared or static library, or you can [add the files to your project](#add-files-to-project).

### Build
```
cd oolog
mkdir build
cd build
cmake ..
make
```
By default, it will build:
- static and shared libraries
- tests
- samples

If you only want to build one of them, add a `target` when calling `make`. Examples:
```
make oolog          // will only build shared library
make oolog-static   // will only build static library
make oologTest      // will only build test suite
make sample_001     // will only build sample 001
```
### Add files to project
Add the `src/oolog.cpp` file to your project and add the `include/` folder as include directory.

If you are going to use any of the printers provided by **oolog**, add the printers you need from `src/printers/xxx.cpp` and add the `include/printers/` folder as include directory to your project.

A C++11 compiler is required.

## Quick Start
Once you have the library in your project, it is as easy to use it as the following code:
```
#include "oolog.h"
#include "printers/ConsoleLogPrinter.h"

void RunApp(oolog::Log& myLog);

int main(){
    std::shared_ptr<oolog::LogPrinter> logPrinter =
        std::make_shared<oolog::EndlLogPrinter>(
        std::make_shared<oolog::ConsoleLogPrinter>());

    oolog::Log log(logPrinter, oolog::LogLevel::Verbose);

    RunApp(log);

    return 0;
}


void RunApp(oolog::Log& myLog) {
    myLog.Info("App has started!");
    myLog.Verbose("hello log!", "add ", "as", "many paramaters as you want");
    int x = 10;
    myLog.Verbose("Combine different types without problem! x = ", x);
    myLog.Info("Closing app...");
}
```
## Log levels
There are the following log levels:
- Fatal
- Error
- Warning
- Info
- Verbose
- Debug

When initializing a oolog::Log object, a log level is required. All logs prior and equal to the level provided will be logged, the others won't.

That rule applies for all levels expect for `Debug` which is treated independently and it's disabled by default. oolog doesn't want to assume how Debug is defined in your system. If you want to enable Debug logs, you only have to call `EnableDebug()` in your log object. Example:
```
oolog::Log log(logPrinter, oolog::LogLevel::Verbose);
#ifdef YOUR_APP_DEBUG
log.EnableDebugLogs();
#endif
```
oolog doesn't accept initialization a log object with Debug level and it will throw an `std::string exception` if that happens.

# Design
The library has been designed to be highly customizable and easy to use while keeping an object oriented approach. There were different points to fulfill:
- Logging should be easy and done through an object which can be passed through the application
- Creating a new log object should be easy
- Adding new log formats or features:
    - should not require to modify the Log class
    - should not affect code using a Log object

The `Log` class provides all the Log functions for each log level. An object of this class is the one that should be passed around the application. There is no limitation in creating more than one Log object. However, **thread safety** is only guaranted within the same log object. Two log objects printing to the exact same resource has undefined behaviours. It is recommended to use the same object in that case.

The constructor takes a reference to a `Printer` object which will be in charge of effectuating the log operation.

With this design, adding a feature to your log (adding a prefix to each log line, logging through HTTP instead of a file or printing the log to console, for instance) only requires to modify a Printer. Or even better, to **decorate** the existing Printer with a new **Decorator** that adds that specific feature.

[Decorator design pattern](https://en.wikipedia.org/wiki/Decorator_pattern) is used to allow customization.

## Log parameters
oolog makes use of the **variadic templates** feature. That means there's no limit in how many parameters are passed to the function neither in their type.

Internally a **std::ostringstream** is used, so a call to log:
```
myLog.Info("Hi, ", "this is ", "log with multiple arguments", x , y, z, myCustomObject);
```
is equivalent to:
```
stream << "Hi, " << "this is " << "log with multiple arguments" << x << y << z << myCustomObject;
```
This means that in order to log custom objects, the *operator<<* for that class must be overloaded. Check `sample 010` to see an example.

## Available Printers
The following printers are provided by oolog (sorted aplhabetically):
- **Console**: prints the log to console (std::cout)
- **Fake**: doesn't print. Useful for unit tests where logs are not required
- **File**: prints to a file
- **RotatedFile**: prints to a file and applies file rotation if it gets a certain size

None of these printers modify the actual log. If NewLine decorator is not used, there won't be line breaks between different log calls.

## Available Decorators
The following decorators are provided by oolog (sorted aplhabetically):
- **ColorANSI**: Adds ANSI color codes to the log. Useful for unix-like systems and for both console and file printers
- **ColorWin32Console**: Adds Win32 Console specific color functionality.
- **Level**: Adds a prefix with the log level as [X] where X is the first letter of the log level. This helps filtering logs (using `grep` for instance)
- **NewLine**: Adds a **std::endl** suffix to the log.
- **Split**: Takes two printer references and calls them. They can also be decorators. Useful to log to multiple resources (check `sample 006`).
- **Timestamp**: Adds a prefix with the timestamp of the log using the format `"%Y/%m/%d %H:%M:%S"`.

## Testing code using oolog
oolog integrates perfectly in test suites (whether they are unit tests or integration tests). You only need to provide a Printer that fulfills your requirements in the test suite.

Furthermore, oolog provides a **FakePrinter** that you can use as test double for your test suite. You won't have to worry about having logs when running your automated tests.

The FakePrinter is actually used to test oolog itself.

# Understanding Decorators stack
When seeing the log initialization with multiple Decorators, it can be a little confusing at the beginning to know what will happen. Let's look at an example:
```
std::shared_ptr<oolog::printers::Printer> logPrinter =
    std::make_shared<oolog::printers::decorators::Level>(
    std::make_shared<oolog::printers::decorators::Timestamp>(
    std::make_shared<oolog::printers::decorators::ColorANSI>(
    std::make_shared<oolog::printers::decorators::NewLine>(
    std::make_shared<oolog::printers::Console>()))));


oolog::Log log(logPrinter, oolog::LogLevel::Verbose);
```
Each Decorator is decorating, ie. adding a decoration, to the content and calling Printer/Decorator below. They will be called in the order they are written.

Following the example, the following steps will happen for a log `myLog.Warning("this is my log")`:
1. Level is called with parameter `"this is my log"` and it will add the LogLevel prefix (`[W] ` in this example)
2. Timestamp is called with parameter `"[W] this is my log"` and adds the timestamp at the beginning
3. ColorANSI is called with parameter `"2018/01/24 12:32:58 [W] this is my log"` and adds the ANSI color code (prefix and sufix)
4. NewLine is called with parameter `"\033[1;33m2018/01/24 12:32:58 [W] this is my log\033[0m"` and adds the `std::endl` sufix
5. Console is called with parameter `"\033[1;33m2018/01/24 12:32:58 [W] this is my log\033[0m\n"` and calls `std::cout`

The resulting log on the console (unix-like) will be:
```
2018/01/24 12:32:58 [W] this is my log
```

# Customization
You can customize how and where to log easily. You can create your own Printers and Decorators to fulfill your requirements. You only need to provide a Printer to the Log object.

## Printers
To create your own Printer, you only need to inherit from the Printer class and implement the `PrintLog()` function:
```
class Printer {
    public:
        virtual void PrintLog(std::string&, LogLevel) = 0;
};
```

This function is only called if the LogLevel is fulfilled.

Then you only need to provide your Printer to the Log class:
```
oolog::Log log(yourCustomPrinter, oolog::LogLevel::Info);
```

## Decorators
Like Printers, to create your own Decorator you only need to inherit from the Decorator class:
```
class Decorator : public Printer {
    public:
        OOLOG_API Decorator(std::shared_ptr<Printer> origin);

        virtual void PrintLog(std::string&, LogLevel) = 0;

    protected:
        void CallOrigin(std::string&, LogLevel);

    private:
        std::shared_ptr<Printer> originLogPrinter;
};
```
And implement the PrintLog function with your needed feature. In this case, you'll have to call the `CallOrigin()` function at the end of PrintLog. Example:
```
class YourOwnDecorator : public oolog::printers::decorators::Decorator {
    public:
        YourOwnDecorator(std::shared_ptr<Printer> origin) : Decorator(std::move(origin)) { }

        virtual void PrintLog(std::string& textToLog, LogLevel logLevel) {
            // Decorate the log
            // ...

            CallOrigin(textToLog, logLevel);
        }
};
```

Testing travis.com

# License
MIT License

Copyright (c) 2018 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


