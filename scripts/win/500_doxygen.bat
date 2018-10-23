SET CURDIR=%~dp0
SET ROOT_DIR=%CURDIR%\..\..\
cd %ROOT_DIR%
SET ROOT_DIR=%cd%

cd build\docs\doxy\CODE

rmdir sn_stl /s /q
rmdir test /s /q

cd %ROOT_DIR%

xcopy /I codes\inc\sn_stl build\docs\doxy\CODE\sn_stl /e
xcopy /I codes\src\test build\docs\doxy\CODE\test /e

cd build\docs\doxy

rmdir doxygen /s /q

call doxyrun_html.bat

cd %CURDIR%