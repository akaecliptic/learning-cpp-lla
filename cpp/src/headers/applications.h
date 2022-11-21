#pragma once

#include <string>
#include <iostream>

class Application {
    protected:
        bool isRunning;
    public:
        virtual int Run() = 0;
};

class ConsoleApplication : public Application {
    public:
        ConsoleApplication();
        int Run() override;
};
