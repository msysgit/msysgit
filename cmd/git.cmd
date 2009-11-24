@rem Do not use "echo off" to not affect any child calls.
@setlocal

@rem Get the abolute path to the parent directory, which is assumed to be the
@rem Git installation root.
@for /F "delims=" %%I in ("%~dp0..") do @set git_install_root=%%~fI
@set PATH=%git_install_root%\bin;%git_install_root%\mingw\bin;%PATH%

@if "%HOME%"=="" @set HOME=%USERPROFILE%
@set PLINK_PROTOCOL=ssh
@if "%LESSCHARSET%"=="" @set LESSCHARSET=latin1

@if "%1"=="gui" @goto gui

:default
@rem Get the current console ("OEM") codepage.
@for /f "tokens=4" %%i in ('chcp') do @set cp_oem=%%i
@rem Get the current GUI ("ANSI") codepage.
@for /f "skip=2 tokens=3" %%i in ('reg query HKLM\SYSTEM\CurrentControlSet\Control\Nls\CodePage /v ACP') do @set cp_ansi=%%i
@rem Set the console codepage to match the GUI codepage.
@chcp %cp_ansi% > nul
@git.exe %*
@rem Restore the original console codepage.
@chcp %cp_oem% > nul
@goto quit 

:gui
@if "%2"=="citool" @goto default
@start wish.exe "%git_install_root%\libexec\git-core\git-gui" -- %2 %3 %4 %5 %6 %7 %8 %9

:quit
@%COMSPEC% /c exit /b %ErrorLevel%
