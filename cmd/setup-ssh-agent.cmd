@echo off

:: Enable extensions, the "verify other 2>nul" is a trick from the setlocal help
verify other 2>nul
setlocal EnableDelayedExpansion
if errorlevel 1 (
    echo Unable to enable extensions
    goto end
)

echo Configuring SSH Agent environment...

:: Start and set environment variables for SSH agent and key insertion
@set GIT_ENV_UTILITY_DIR=%~dp0..\etc\
for /f "delims=" %%a in ('cscript.exe /nologo ^"!GIT_ENV_UTILITY_DIR!git-env-utility.js^" /gitbindir:p /p /home:v /startsshagent:v') do (
    endlocal
    @set %%a
)

:: Set or reset SSH keys for current SSH agent
call "%GIT_BIN_DIR%\ssh-add.exe"

:end
