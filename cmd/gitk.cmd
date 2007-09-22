@echo off
for /F %%I in ("%~dp0..") do set path=%%~fI\bin;%%~fI\mingw\bin
set home=%HOMEDRIVE%%HOMEPATH%
start /B sh.exe /bin/gitk %*
