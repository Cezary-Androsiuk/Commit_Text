#include "func.hpp"

void logStatus(const std::string &logFile, const std::string &statusToLog, const Date &date)
{
    std::ofstream file;

    std::string time = date.getDate() + " " + date.getTime();

    file.open(logFile, std::ios::app);
    file << "start(" << time << ") - (" << statusToLog << ") - end(" << time << ")\n";
    file.close();
}

std::string makeMyDayAction(const Date &date, const std::string &formulaFile)
{
    Formula formula(formulaFile);
    formula.load();

    // check that the file containing the formula exists
    if (formula.isTextFileMissing())
    {
        printf("makeMyDayAction() Terminated cause missing formula text file\n");
        return "missing formula text file";
    }

    formula.print();
    printf("\n\n");

    for (int i = 0; i < 100; i++)
    {
        int state = formula.update(START_DATE, date);
        if (state == Formula::BEFORE_START)
        {
            printf("before start\n");
            return "9"; //"Before start date";
        }
        else if(state == Formula::AFTER_END)
        {
            printf("after end - script could be terminated\n");
            return "8";
        }
        else if (state == Formula::NONE_FIELD_AND_SETTED)
        {
            printf("empty field\n");
            return "1"; //"Today's field should remain empty";
        }
        else if (state == Formula::VALUE_FIELD_AND_FILLED_MAX)
        {
            printf("field maxed\n");
            return "2"; //"Today's field has already been filled";
        }

        formula.print();
        printf("\n\n");

        formula.save();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::string add("git add \"");
        add += formulaFile + "\"";
        std::system(add.c_str());
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::string commit("git commit -m \"");
        commit += date.getDate() + " " + date.getTime() + " Index: " + to_str(i) + "\"";
        std::system(commit.c_str());
    }
    
    std::system("git push");
    return " "; //"Today's field has been filled correctly";
}