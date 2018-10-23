SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

cd deps\win\OpenCppCoverage
set PATH=%PATH%;%cd%
cd %ROOT_DIR%

rmdir build\docs\opencpp /s /q

OpenCppCoverage --sources codes --excluded_sources *.cpp --export_type html:build\docs\opencpp -- build\Debug\sn_stl.exe  

del LastCoverageResults.log

cd %CURDIR%