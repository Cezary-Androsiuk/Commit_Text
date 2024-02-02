#include "func.hpp"

std::string makeMyDayAction(Date date)
{
    Text text;
    if (text.isTextFileMissing())
    {
        printf("makeMyDayAction() Terminated cause missing text file\n");
        return "missing text file";
    }
    text.print();
    printf("\n\n");

    for (int i = 0; i < 100; i++)
    {
        int state = text.test(date);
        if (state == Text::BEFORE_START)
        {
            printf("before start\n");
            return "9"; //"Before start date";
        }
        else if (state == Text::NONE_FIELD_AND_SETTED)
        {
            printf("empty\n");
            return "1"; //"Today's field should remain empty";
        }
        else if (state == Text::VALUE_FIELD_AND_FILLED_MAX)
        {
            printf("max\n");
            return "2"; //"Today's field has already been filled";
        }

        text.print();
        printf("\n\n");

        text.setState();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::system("git add text");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::string commit("git commit -m \"");
        commit += date.getDate() + " " + date.getTime() + " Index: " + to_str(i) + "\"";
        std::system(commit.c_str());
    }
    // text.print();
    std::system("git push");
    return " "; //"Today's field has been filled correctly";
}

void makeTaskScheduler()
{
    const std::filesystem::path autorun_path(R"(C:\Users\cezar\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup)");
    const std::string autorun_file(R"(task_scheduler_for_send_nudes_git_repo.exe)");
}