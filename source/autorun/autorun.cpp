#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <filesystem>
#include <iostream>

#include "../json_XD.hpp"

// time facilities
// example:  if you want 13 hours as a seconds use H_TO_S(13) instead of 46'800 or 13*60*60
#define S_TO_S(x) (x)                   /* seconds to seconds */
#define M_TO_S(x) (x * 60)              /* minutes to seconds */
#define H_TO_S(x) (x * 60 * 60)         /* hours to seconds */
#define D_TO_S(x) (x * 60 * 60 * 24)    /* days to seconds */

// the time at which the application should start
#define APP_START_TIME (H_TO_S(0) + M_TO_S(10) + S_TO_S(0))

#define TERMINATE_PATH_FILE_FSP AUTORUN_PATH_FSP / TERMINATE_FILE_STR

bool shouldContinueScript(){
    // test if the file (from TERMINATE_PATH_FILE_FSP) exists. If so, stop the application.
    if(!std::filesystem::exists(TERMINATE_PATH_FILE_FSP))
        return true;
    
    // pause, to avoid this script deleting the file under TERMINATE_PATH_FILE_FSP 
    // before the script that created it has checked that the file was created correctly. 
    // Just as a precaution.
    std::this_thread::sleep_for(std::chrono::seconds(2));

    if(std::filesystem::exists(TERMINATE_PATH_FILE_FSP)){
        std::filesystem::remove(TERMINATE_PATH_FILE_FSP);
        return false; // stop program
    }
    return true;
}

void runApplication(){
    // starts application

    // save current path
    auto start_path(std::filesystem::current_path());
    
    // change current path
    std::filesystem::current_path(RUN_PATH_STR);
    std::system(("start " + RUN_FILE_STR).c_str());

    // restore current path
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

    // the time is reset to the beginning of the day, as adding a day to the current time may cause the start time to shift
    // e.g. maybe not every day but every few days the application will be launched a second later, 
    // this delay will add up to a daily launch and on a larger scale this can lead to significant shifts in launch times 

    // // debug purposes
    // // char buffer[32];
    // // std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&next_run));

    return next_run;
}

int main(){
    // hide terminal
    FreeConsole();

    // start application just after reboot
    runApplication();
    std::time_t next_run_time = nextDayRunTime();

    while(shouldContinueScript()){
        std::time_t current_time = std::time(nullptr);
        if(current_time >= next_run_time){
            runApplication();
            next_run_time = nextDayRunTime();
        }

        std::this_thread::sleep_for(REFRESH_TIME_CHRONO);
    }
    
    // Refreshing is important to terminate_autorun works. 
    // Additionally, the app can't simply wait until the next day, as it won't work after the PC falls asleep.

    // I changed this because when I was playing, it was annoying to start the app every two hours, and once I even died in game. :c
}