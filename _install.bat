@echo off
set "autorun=C:\Users\cezar\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\autorun-send_nudes.exe"

if exist "%autorun%" (
    echo error: program was already installed
    pause
) else (
    echo installing program...
    @REM compile autorun
    g++ "source\autorun\autorun.cpp" -o "source\autorun\autorun.exe"
    @REM compile terminator
    g++ "source\terminate_autorun\terminate_autorun.cpp" -o "source\terminate_autorun\terminate_autorun.exe"
    @REM compile main script
    g++ "source\main\main.cpp" "source\main\func.cpp" "source\main\Date.cpp" "source\main\Formula.cpp" "source\main\PreventRun.cpp" -o "source\main\main.exe"


    @REM copy autorun to autorun path and set file name
    copy "source\autorun\autorun.exe" "%autorun%"
    @REM copy script to main directory
    copy "source\main\main.exe" "main-send_nudes.exe"

    @REM start autorun
    start "" "%autorun%"
    pause
)

exit