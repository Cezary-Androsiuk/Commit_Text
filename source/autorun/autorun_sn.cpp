#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <windows.h>
#include <filesystem>

// compile:
// g++ autorun_sn.cpp -o "C:\Users\cezar\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\autorun_sn.exe" && explorer "C:\Users\cezar\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"

const std::filesystem::path run_path(R"(C:\Users\cezar\Desktop\Send Nudes Git Repo)");
constexpr const char *run_file_name = "main.exe";

constexpr const char *terminate_file_name = "Stop_autorun_script.tmp";

// run program delay in minutes
#define RUN_DELAY 120

bool testIfExtit(){
    // after finding a file, wait and then check again
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
    // std::ofstream file("file.log", std::ios::app);
    // std::time_t t = std::time(nullptr);
    // std::tm *now = std::localtime(&t);
    // file << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << std::endl;
    // file.close();
    
    auto start_path(std::filesystem::current_path());
    std::filesystem::current_path(run_path);
    std::system((std::string("start ") + run_file_name).c_str());
    std::filesystem::current_path(start_path);
}

int main(){
    // hide terminal
    FreeConsole();

    runApplication();
    int iterator = 0;
    while(testIfExtit()){

        if(iterator >= RUN_DELAY){
            iterator = 0;
            runApplication();
        }

        // std::this_thread::sleep_for(std::chrono::seconds(1)); // debug
        std::this_thread::sleep_for(std::chrono::minutes(1)); // release
        iterator ++;
    }


}