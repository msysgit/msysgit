@rem Do not use "echo off" to not affect any child calls.
@setlocal

@rem Get the abolute path to the current directory, which is assumed to be the
@rem Git installation root.

@for /F "delims=" %%I in ("%~dp0") do @set git_install_root=%%~fI
@set PATH=%git_install_root%\bin;%git_install_root%\mingw\bin;%git_install_root%\cmd;%PATH%

@REM http://markashleybell.com/articles/portable-git-windows-setting-home-environment-variable
@if not exist "%HOME%" @set HOME=%HOMEDRIVE%%HOMEPATH%
@if not exist "%HOME%" @set HOME=%USERPROFILE%
@if not exist "%TERM%" @set TERM=msys

@REM You can set git to be verbose by uncommenting the next line
@REM
@REM SET GIT_CURL_VERBOSE=1

@REM from inside enterprise intranets you perhaps have to use a proxy server to access the intranet
@REM http://stackoverflow.com/questions/128035/how-do-i-pull-from-a-git-repository-through-an-http-proxy
@REM
@REM ask your IT department for the address and port of their proxy
@REM SET HTTPS_PROXY=http://proxy.internal.example.com:8080

@set PLINK_PROTOCOL=ssh

@REM @cd %HOME%
@REM change to drive c: and to your local \work directory on that drive
@c:
@cd\work

@REM start a new command shell 
@REM with a meaning full window title 
@REM with cmd.exe 
@REM with parameters

@REM http://stackoverflow.com/questions/154075/using-the-dos-start-command-with-parameters-passed-to-the-started-program
@REM http://ss64.com/nt/cmd.html
@start "Portable git shell" %COMSPEC% /K "@ECHO *** Welcome to your portable git shell *** & git --version"
