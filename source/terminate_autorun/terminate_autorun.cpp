#include <cstdio>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>

#include "../json_XD.hpp"

#define TERMINATE_PATH_FILE_FSP AUTORUN_PATH_FSP / TERMINATE_FILE_STR
#define AUTORUN_PATH_FILE_FSP AUTORUN_PATH_FSP / AUTORUN_FILE_STR

int main(){
    // check if terminate file already exist in destination
    if(std::filesystem::exists(TERMINATE_PATH_FILE_FSP)){
        printf("Terminating already in progress!\n");
        
        std::system("pause");
        return 1; 
    }

    // create terminate file
    std::fstream(TERMINATE_PATH_FILE_FSP, std::ios::out);

    // check if file was created correctly
    if(!std::filesystem::exists(TERMINATE_PATH_FILE_FSP)){
        printf("Cannot create file!");
        std::system("pause");
        return 1;
    }

    printf("Started termination. That should take up to " REFRESH_TIME_TEXT " (autorun refresh time).\n");

    // wait until file is deleted by autorun
    while(std::filesystem::exists(TERMINATE_PATH_FILE_FSP)){
        printf("waiting (10s) for autorun_sn.exe response... \n");
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    // if file was deleted, that means process was stopped
    // autorun file will be deleted after that 
    printf("Removing autorun_sn.exe...\n");
    std::filesystem::remove(AUTORUN_PATH_FILE_FSP);

    if(std::filesystem::exists(AUTORUN_PATH_FILE_FSP))
    {
        printf("Program terminated but can't delete '%s' file!\n", (AUTORUN_PATH_FILE_FSP).c_str());
        std::system("pause");
        return 1;
    }
    else
        printf("Program terminated and '%s' removed!\n", (AUTORUN_PATH_FILE_FSP).string().c_str());
    
    std::system("pause");
    return 0;
}