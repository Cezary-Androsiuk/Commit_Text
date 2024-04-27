#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <filesystem>
#include <iostream>

// compile:
// g++ autorun_sn.cpp -o "C:\Users\cezar\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\autorun_sn.exe" && explorer "C:\Users\cezar\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"


// how often this application will check if is time to die
#define REFRESH_TIME_CHRONO std::chrono::minutes(1)

// time facilities
// example:  if you want 13 hours as a seconds use H_TO_S(13) instead of 46'800 or 13*60*60
#define S_TO_S(x) (x)
#define M_TO_S(x) (x * 60)
#define H_TO_S(x) (x * 60 * 60)
#define D_TO_S(x) (x * 60 * 60 * 24)
#define APP_START_TIME (H_TO_S(0) + M_TO_S(10) + S_TO_S(0))


const std::filesystem::path run_path(R"(C:\Users\cezar\Desktop\Send Nudes Git Repo)");
constexpr const char *run_file_name = "main.exe";

constexpr const char *terminate_file_name = "Stop_autorun_script.tmp";



bool testIfExit(){
    // test if the file (from terminate_autorun) exists. If so, stop the application.

    if(!std::filesystem::exists(terminate_file_name))
        return true;
    // sleep to avoid a situation where the terminating file is deleted before the \
        terminating program checks whether the file has been created successfully
    std::this_thread::sleep_for(std::chrono::seconds(2));

    if(std::filesystem::exists(terminate_file_name)){
        std::filesystem::remove(terminate_file_name);
        return false; // stop program
    }
    return true;
}

void runApplication(){
    // starts application

    auto start_path(std::filesystem::current_path());
    std::filesystem::current_path(run_path);
    std::system((std::string("start ") + run_file_name).c_str());
    std::filesystem::current_path(start_path);
}

std::time_t nextDayRunTime(){
    // returns how much minutes left till next run

    std::time_t current_time = std::time(nullptr);
    std::tm* now = std::localtime(&current_time);
    
    // move to begining of today (remove time)
    std::time_t next_run = current_time - H_TO_S(now->tm_hour) - M_TO_S(now->tm_min) - S_TO_S(now->tm_sec);
    // add time on what app should start the next day
    next_run += APP_START_TIME + D_TO_S(1);
    // At this point, this is the estimated time when the application will be started.
    
    // debug purposes
    // char buffer[32];
    // std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&next_run));

    return next_run;
}

int main(){
    // hide terminal
    FreeConsole();

    // start application after reboot
    runApplication();
    std::time_t next_run_time = nextDayRunTime();

    while(testIfExit()){
        std::time_t current_time = std::time(nullptr);

        if(current_time >= next_run_time){
            runApplication();
            next_run_time = nextDayRunTime();
        }

        std::this_thread::sleep_for(REFRESH_TIME_CHRONO);
    }
    
    // Refresh is important to terminate_autorun works. \
        Additionally, the app can't simply wait until the next day, as it won't work after the PC falls asleep.

    // I changed that because when i was playing, starting app every two hours was just annoying and once i even died in game :c
}