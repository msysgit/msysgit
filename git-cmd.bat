@set PLINK_PROTOCOL=ssh
@setlocal
@for /F "delims=" %%I in ("%~dp0") do @set git_install_root=%%~fI
@set path=%git_install_root%\bin;%git_install_root%\mingw\bin;%git_install_root%\cmd;%PATH%
@if "%HOME%"=="" @set HOME=%USERPROFILE%
@cd %HOME%
@start %COMSPEC%
