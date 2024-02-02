#include "PreventRun.hpp"

PreventRun::PreventRun() : running_file("program_is_running")
{
    if (std::filesystem::exists(this->running_file))
    {
        std::ofstream file("scheduler.log", std::ios::app);
        printf("prevented double run!\n");
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