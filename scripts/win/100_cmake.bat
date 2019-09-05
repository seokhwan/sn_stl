SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

cd deps\win\cmake-3.15.3-win64-x64\bin
set PATH=%PATH%;%cd%
cd ..\..\..\..\

rmdir build /s /q
mkdir build

cd build
cmake ..\codes\ -G "Visual Studio 16 2019" -A x64

cd %CURDIR%
