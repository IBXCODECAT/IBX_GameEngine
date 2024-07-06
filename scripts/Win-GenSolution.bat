@echo off
rem This script generates the Visual Studio 2022 solution file using Premake
echo Running Premake...

pushd %~dp0..
call "vendor/premake/premake5.exe" vs2022
popd

IF %ERRORLEVEL% NEQ 0 (
    color 0C
    PAUSE
)