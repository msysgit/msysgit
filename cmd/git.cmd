@rem Do not use "echo off" to not affect any child calls.
@setlocal

@rem Get the abolute path to the parent directory, which is assumed to be the
@rem Git installation root.
@for /F "delims=" %%I in ("%~dp0..") do @set git_install_root=%%~fI
@set PATH=%git_install_root%\bin;%git_install_root%\mingw\bin;%PATH%

@if not exist "%HOME%" @set HOME=%HOMEDRIVE%%HOMEPATH%
@if not exist "%HOME%" @set HOME=%USERPROFILE%

@set PLINK_PROTOCOL=ssh

@if "%1"=="gui" @goto gui

:default
@rem Get the current console ("OEM") codepage.
@for /f %%i in ('getcp -oem') do @set cp_oem=%%i
@rem Get the current GUI ("ANSI") codepage.
@for /f %%i in ('getcp -ansi') do @set cp_ansi=%%i
@rem Set the console codepage to match the GUI codepage.
@chcp %cp_ansi% > nul < nul
@git.exe %*
@set ErrorLevel=%ErrorLevel%
@rem Restore the original console codepage.
@chcp %cp_oem% > nul < nul
@goto quit 

:gui
@if "%2"=="citool" @goto default
@for /f "tokens=1-1*" %%a in ("%*") do @set args=%%b
@start "git-gui" wish.exe "%git_install_root%\libexec\git-core\git-gui" -- %args%

:quit
@"%COMSPEC%" /c exit /b %ErrorLevel%
