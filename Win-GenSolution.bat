@echo off
rem This script generates the Visual Studio 2022 solution file using Premake and updates the GitHub submodules.
rem Notify the user that premake is running
color 0A
echo Running Premake...

rem Run Premake to generate Visual Studio 2022 solution

%~dp0../vendor/premake/premake5.exe vs2022

IF %ERRORLEVEL% NEQ 0 (
    PAUSE
)