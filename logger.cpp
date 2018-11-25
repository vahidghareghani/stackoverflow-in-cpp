#pragma once

#include <iostream>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <vector>
#include "logger.h"
#include "User.h"


int x=0;
Logger::Logger() {}

Logger& Logger::getInstance() {
    static Logger lg;
    return lg;
}


std::ofstream& operator <<(std::ofstream& of, User& user){
    std::string file = "Log." + to_string(x) + ".txt";
    ofstream fout(file);
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t tt;
    tt = std::chrono::system_clock::to_time_t(today);
    of << user.email << ctime(&tt) << endl;
    return of;
}

void Logger::log(User& user) {
    ifstream fi("log.txt");
    fi >> x;
    x++;
    ofstream fo("log.txt");
    fo << x;
    fout << user << endl;
}

