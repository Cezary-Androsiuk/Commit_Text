#ifndef JSON_XD_HPP
#define JSON_XD_HPP

/*---------------------------- ABOUT DESIGNATIONS  ----------------------------*/
// prefix comment means where #define will be used 
// (SCRIPT: S, AUTORUN: A, TERMINATE: T)


/*---------------------------- SHOULD BE CHANGED FOR OWN USE ----------------------------*/

// date from which the script will start committing changes
// the preferred starting day for Github is Sunday (otherwise good luck)
/* S-- */ #define START_DATE Date(2024, Month::January, 28)

// path in what file to execute is located
/* -A- */ #define RUN_PATH_STR std::string(R"(C:\Users\cezar\Desktop\Send Nudes Git Repo)")

// name of file to execute
// ! must be identical to the name in the installer
/* -A- */ #define RUN_FILE_STR std::string("main-send_nudes.exe")

// the name of the file that automatically runs the script
// ! must be identical to the name in the installer
/* --T */ #define AUTORUN_FILE_STR std::string("autorun-send_nudes.exe")

// path to the files that will be launched at boot time
// ! must be identical to the path in the installer
/* -AT */ #define AUTORUN_PATH_FSP std::filesystem::path(R"(C:\Users\cezar\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup)")




/*---------------------------- COULDB BE CHANGED IF NEEDED ----------------------------*/

// a file in which logs will be saved each time the script is run
/* S-- */ #define LOG_FILE "scheduler.log"

// file containing the text formula
/* S-- */ #define FORMULA_FILE "textFormula.txt"

// how often autorun app will check if is time to die
/* -A- */ #define REFRESH_TIME_CHRONO std::chrono::minutes(1)

// just to inform user about estimated time (related with REFRESH_TIME_CHRONO)
/* --T */ #define REFRESH_TIME_TEXT "one minute"

// the name of the file the autorun script will look for each time it refreshes. 
// if the file exists the autorun script will disable itself. 
// file is created by terminate script 
/* -AT */ #define TERMINATE_FILE_STR std::string("Stop_autorun_script")

#endif // JSON_XD_HPP