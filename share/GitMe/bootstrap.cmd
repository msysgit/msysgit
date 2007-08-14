@echo off

title Git for Windows (Dev) Installer

echo.
echo Installing Git development environment for Windows
echo.

set INSTALL_ROOT=%cd%
set INSTALL_DIR=%~dp0

%INSTALL_DIR%\bin\sh.exe /bootstrap.sh

if NOT EXIST %INSTALL_DIR%\setup-msysgit.sh call :error Unable to fetch installation files
%INSTALL_DIR%\bin\sh.exe /setup-msysgit.sh
if ERRORLEVEL 1 call :error Setting up MSys failed

if NOT EXIST %INSTALL_ROOT%\msys.bat call :error Unable to start MSys
%INSTALL_ROOT%\msys.bat

rem We never actually return here from msys.bat

goto :eof

rem ==============

:error
echo.
echo Error: %*
echo.
echo INSTALLATION ABORTED !!!
pause
exit 1
