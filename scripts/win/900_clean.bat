SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

rmdir build /s /q 
rmdir doc /s /q
rmdir codes/.vs /s /q

cd %CURDIR%