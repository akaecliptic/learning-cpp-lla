@echo off

set msvc="c:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat"

if "%~1" == "compile" ( goto compile )
if "%~1" == "run" ( goto run )
if "%~1" == "" ( goto execute )

:compile
    if not defined devmode ( call %msvc% )

    if errorlevel 0 ( set devmode=1 )

    cl /Fo"./objects/" /std:c++17 /EHsc app.cpp ./libs/sqlite/sqlite3.c ./src/*.cpp ./src/dao/*.cpp ./src/models/*.cpp

    if errorlevel 1 (
        echo: 
        echo compilation error. please check above.
    ) else (
        cls
        echo compilation success. 
    )

if "%~1" == "compile" ( goto end )

:run
    echo Running application: 
    echo:
    app.exe
goto end

:execute
    goto compile
    goto run

:end
echo exiting with - %errorlevel%
