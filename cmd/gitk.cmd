@echo off
set MSYSGIT_SAVED_PATH=%PATH%
set MSYSGIT_SAVED_HOME=%HOME%
for /F "delims=" %%I in ("%~dp0..") do set path=%%~fI\bin;%%~fI\mingw\bin
if "%HOME%"=="" set HOME=%USERPROFILE%
start /B sh.exe /bin/gitk %*
set PATH=%MSYSGIT_SAVED_PATH%
set HOME=%MSYSGIT_SAVED_HOME%
