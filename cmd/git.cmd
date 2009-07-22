@set PLINK_PROTOCOL=ssh
@setlocal
@for /F "delims=" %%I in ("%~dp0..") do @set git_install_root=%%~fI
@set path=%git_install_root%\bin;%git_install_root%\mingw\bin;%PATH%
@if "%HOME%"=="" @set HOME=%USERPROFILE%
@if "%1"=="gui" @goto gui
:default
@git.exe %*
@exit /b %ErrorLevel%
:gui
@if "%2"=="citool" @goto default
@start wish.exe "%git_install_root%\libexec\git-core\git-gui" -- %2 %3 %4 %5 %6 %7 %8 %9
