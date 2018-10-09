SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

cd deps_win\OpenCppCoverage
set PATH=%PATH%;%cd%
cd ..\..\

rmdir doc\opencpp /s /q

OpenCppCoverage --sources codes\sn_stl --excluded_sources *.cpp --export_type html:doc\opencpp -- codes\x64\Debug\sn_stl.exe  

cd %CURDIR%