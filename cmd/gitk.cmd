@setlocal
@for /F "delims=" %%I in ("%~dp0..") do @set git_install_root=%%~fI
@set path=%git_install_root%\bin;%git_install_root%\mingw\bin;%PATH%
@if "%HOME%"=="" @set HOME=%USERPROFILE%
@start wish.exe "%git_install_root%\bin\gitk" -- %*
