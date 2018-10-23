SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

cd build

if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat" call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat"


if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat" call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"




MSBuild.exe sn_stl.sln /property:Configuration=Release /property:Platform=x64
MSBuild.exe sn_stl.sln /property:Configuration=Debug /property:Platform=x64

cd %CURDIR%