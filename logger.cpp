#pragma once

#include <iostream>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <vector>
#include "logger.h"
#include "User.h"


int x=0, flag=1;
Logger::Logger() {}

Logger& Logger::getInstance() {
    static Logger lg;
    return lg;
}


std::ofstream& operator <<(std::ofstream& of, User& user){
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t tt;
    tt = std::chrono::system_clock::to_time_t(today);
    std::string file = "Log." + to_string(x) + ".txt";
    of.open(file, std::ios_base::app);
    of << user.email << " " << ctime(&tt);
    of.close();
    return of;
}

void Logger::log(User& user) {
    if(flag){
        ifstream fi("log.txt");
        fi >> x;
        fi.close();
        x++;
        ofstream fo("log.txt");
        fo << x;
        flag=0;
        fo.close();
    }
    fout << user << endl;
}

