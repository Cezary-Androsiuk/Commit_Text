#include <cstdio>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>

// compile:
// g++ terminate_autorun_sn.cpp -o ../../terminate_autorun_sn.exe

// const std::filesystem::path autorun_path(R"(.)"); // debug
const std::filesystem::path autorun_path(R"(C:\Users\cezar\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup)"); // release
constexpr const char *autorun_sn_file = "autorun_sn.exe";
constexpr const char *terminate_file_name = "Stop_autorun_script.tmp";

#define FILE autorun_path / terminate_file_name

int main(){
    if(std::filesystem::exists(FILE)){
        printf("Terminating already in progress!\n");
        
        // std::filesystem::remove(FILE); // debug
        exit(1); // release
    }

    printf("Started termination. That should take up to one minute.\n");
    std::fstream(FILE, std::ios::out);

    if(!std::filesystem::exists(FILE)){
        printf("Cannot create file!");
        exit(1);
    }

    while(std::filesystem::exists(FILE)){
        printf("waiting (10s) for autorun_sn.exe response... \n");
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    printf("Removing autorun_sn.exe...\n");
    std::filesystem::remove(autorun_path / autorun_sn_file);
    printf("Program terminated and autorun_sn.exe removed!\n");
    std::system("pause");
}