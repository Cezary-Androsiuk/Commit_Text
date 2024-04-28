#include "PreventRun.hpp"

PreventRun::PreventRun(const std::string &logFile) : running_file("program_is_running")
{
    if (std::filesystem::exists(this->running_file))
    {
        printf("prevented double run!\n");
        std::ofstream file(logFile, std::ios::app);
        file << "(prevented double run) ";
        file.close();

        std::system("pause");
        exit(0);
    }
    
    std::ofstream file(this->running_file);
    file << "hi :)\n";
    file.close();
}
PreventRun::~PreventRun()
{
    if (std::filesystem::exists(this->running_file))
        std::filesystem::remove(this->running_file);
}