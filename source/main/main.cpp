#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

#include "PreventRun.hpp"
#include "func.hpp"

// compile:
// g++ main.cpp Date.cpp func.cpp PreventRun.cpp Text.cpp -o ..\..\main.exe

int main()
{
    PreventRun prevent_run;
    Date date;
    std::ofstream file;

    file.open("scheduler.log", std::ios::app);
    file << "start(" << date.getDate() << " " << date.getTime() << ") - ";
    file.close();

    std::string result = makeMyDayAction(date);

    file.open("scheduler.log", std::ios::app);
    file << "(" << result << ") - ";
    file << "end(" << date.getDate() << " " << date.getTime() << ")\n";
    file.close();
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // std::system("pause");
}

/*

"Well, this code is a mess, and I don't want to make it clearer...
I will just leave it as it is."

- Czarek from the future: "I've just cleaned up a little bit by moving functions and classes to other files. You are welcome."

*/