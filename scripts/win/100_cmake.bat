SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

cd deps\win\cmake-3.12.3-win64-x64\bin
set PATH=%PATH%;%cd%
cd ..\..\..\..\

rmdir build /s /q
mkdir build

cd build
cmake ..\codes\ -G "Visual Studio 15 2017 Win64"

cd %CURDIR%