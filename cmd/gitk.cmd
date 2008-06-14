@echo off
setlocal
for /F "delims=" %%I in ("%~dp0..") do set path=%%~fI\bin;%%~fI\mingw\bin;%PATH%
if "%HOME%"=="" set HOME=%USERPROFILE%
start /B sh.exe /bin/gitk %*
