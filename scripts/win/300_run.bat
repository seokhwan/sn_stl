SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

build\Debug\sn_stl.exe

build\Release\sn_stl.exe

cd %CURDIR%