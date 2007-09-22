@echo off
for /F %%I in ("%~dp0..") do set path=%%~fI\bin;%%~fI\mingw\bin
set home=%HOMEDRIVE%%HOMEPATH%
git.exe %*
