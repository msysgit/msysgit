@rem Do not use "echo off" to not affect any child calls.

@rem Enable extensions, the `verify other 2>nul` is a trick from the setlocal help
@verify other 2>nul
@setlocal enableDelayedExpansion
@if errorlevel 1 (
    @echo Unable to enable delayed expansion. Immediate expansion will be used.
    @goto fallback
)

@rem Get the absolute path to the parent directory, which is assumed to be the
@rem Git installation root.
@for /F "delims=" %%I in ("%~dp0..") do @set git_install_root=%%~fI
@set PATH=!git_install_root!\bin;!git_install_root!\mingw\bin;!PATH!

@if not exist "!HOME!" @set HOME=!HOMEDRIVE!!HOMEPATH!
@if not exist "!HOME!" @set HOME=!USERPROFILE!

@start "gitk" wish.exe "!git_install_root!\bin\gitk" -- %*
@goto end

:fallback
@rem The above script again with immediate expansion, in case delayed expansion
@rem is unavailable.
@for /F "delims=" %%I in ("%~dp0..") do @set git_install_root=%%~fI
@set PATH=%git_install_root%\bin;%git_install_root%\mingw\bin;%PATH%

@if not exist "%HOME%" @set HOME=%HOMEDRIVE%%HOMEPATH%
@if not exist "%HOME%" @set HOME=%USERPROFILE%

@start "gitk" wish.exe "%git_install_root%\bin\gitk" -- %*

:end
@rem End of script
