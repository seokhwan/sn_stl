SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

start /b dotnet deps\sates\bin\sates_core.dll

timeout /t 3

build\Release\sn_stl.exe

timeout /t 3

cd %CURDIR%