@echo off

rem Enable extensions, the `verify other 2>nul` is a trick from the setlocal help
verify other 2>nul
setlocal EnableDelayedExpansion
if errorlevel 1 (
    echo Unable to enable extensions
    goto failure
)

rem Start the ssh-agent if needed by git
for %%i in ("git.exe") do set GIT=%%~$PATH:i
if exist "%GIT%" (
    rem Get the ssh-agent executable
    for %%i in ("ssh-agent.exe") do set SSH_AGENT=%%~$PATH:i
    if not exist "%SSH_AGENT%" (
        for %%s in ("%GIT%") do set GIT_DIR=%%~dps
        for %%s in ("!GIT_DIR!") do set GIT_DIR=!GIT_DIR:~0,-1!
        for %%s in ("!GIT_DIR!") do set GIT_ROOT=%%~dps
        for %%s in ("!GIT_ROOT!") do set GIT_ROOT=!GIT_ROOT:~0,-1!
        for /D %%s in ("!GIT_ROOT!\bin\ssh-agent.exe") do set SSH_AGENT=%%~s
        if not exist "!SSH_AGENT!" (
            goto ssh-agent-done
        )
    )
    rem Get the ssh-add executable
    for %%s in ("!SSH_AGENT!") do set BIN_DIR=%%~dps
    for %%s in ("!BIN_DIR!") do set BIN_DIR=!BIN_DIR:~0,-1!
    for /D %%s in ("!BIN_DIR!\ssh-add.exe") do set SSH_ADD=%%~s
    if not exist "!SSH_ADD!" (
        goto ssh-agent-done
    )
    rem Check if the agent is running
    for /f "tokens=1-2" %%a in ('tasklist /fi "imagename eq ssh-agent.exe"') do (
        echo %%b | findstr /r /c:"[0-9][0-9]*" > nul
        if "!errorlevel!" == "0" (
            set SSH_AGENT_PID=%%b
        )
    )
    rem Connect up the current ssh-agent
    if [!SSH_AGENT_PID!] == [] (
        echo Removing old ssh-agent sockets
        for /d %%d in (%TEMP%\ssh-??????*) do rmdir /s /q %%d
    ) else (
        echo Found ssh-agent at !SSH_AGENT_PID!
        for /d %%d in (%TEMP%\ssh-??????*) do (
            for %%f in (%%d\agent.*) do (
                set SSH_AUTH_SOCK=%%f
                set SSH_AUTH_SOCK=!SSH_AUTH_SOCK:%TEMP%=/tmp!
                set SSH_AUTH_SOCK=!SSH_AUTH_SOCK:\=/!
            )
        )
        if not [!SSH_AUTH_SOCK!] == [] (
            echo Found ssh-agent socket at !SSH_AUTH_SOCK!
        ) else (
            echo Failed to find ssh-agent socket
            set SSH_AGENT_PID=
        )
    )
    rem See if we have the key
    "!SSH_ADD!" 1>nul 2>nul
    set result=!ERRORLEVEL!
    if not !result! == 0 (
        if !result! == 2 (
            echo|set /p=Starting ssh-agent:
            for /f "tokens=1-2 delims==;" %%a in ('"!SSH_AGENT!"') do (
                if not [%%b] == [] (
                    set %%a=%%b
                )
            )
            echo. done
        )
        set "HOME=%USERPROFILE%"
        "!SSH_ADD!"
        echo.
    )
)

:ssh-agent-done
:failure

endlocal & set "SSH_AUTH_SOCK=%SSH_AUTH_SOCK%" ^
         & set "SSH_AGENT_PID=%SSH_AGENT_PID%"

echo %cmdcmdline% | findstr /l "\"\"" >nul
if not errorlevel 1 (
    call cmd %*
)

