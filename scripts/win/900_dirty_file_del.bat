SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

cd codes

rmdir Debug /s /q
rmdir Release /s /q
rmdir x64 /s /q

rmdir .vs /s /q

rmdir sn_stl\x64 /s /q
rmdir sn_stl\Debug /s /q
rmdir sn_stl\Release /s /q


cd %CURDIR%