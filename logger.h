#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "User.h"

class Logger {
public:
    static Logger& getInstance();
public:
//    void readAndWriteX();
    void log(User& user);
private:
    Logger();
    std::ofstream fout;
};