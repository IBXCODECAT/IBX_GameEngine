

@echo off
rem This script generates the Visual Studio 2022 solution file using Premake and updates the GitHub submodules.
rem Notify the user that premake is running
color 0A
echo Running Premake...

rem Run Premake to generate Visual Studio 2022 solution
@echo on
%~dp0vendor/premake/premake5.exe vs2022

@echo off
rem Notify the user that submodules are being initialized and updated
echo Initializing and Updating GitHub submodules...

start %~dp0update_submodules.sh

rem Pause the script to allow the user to read the output
pause