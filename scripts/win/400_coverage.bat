SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

cd deps_win\OpenCppCoverage
set PATH=%PATH%;%cd%
cd ..\..\

rmdir doc\opencpp /s /q

OpenCppCoverage --sources codes --excluded_sources *.cpp --export_type html:doc\opencpp -- build\Debug\sn_stl.exe  

del LastCoverageResults.log

cd %CURDIR%