#include <string>

#include "PreventRun.hpp"
#include "func.hpp"
#include "../json_XD.hpp"

int main()
{
    PreventRun prevent_run(LOG_FILE);
    Date date;

    std::string resultStatus = makeMyDayAction(date, FORMULA_FILE);
    logStatus(LOG_FILE, resultStatus, date);
    
}

/*

"Well, this code is a mess, and I don't want to make it clearer...
I will just leave it as it is."

- Czarek from the future: "I've just cleaned up a little bit by moving functions and classes to other files. You are welcome."

- Czarek from even further in the future: "Well, DeepL AI helped but I further improved the code and described probably everything." 

*/