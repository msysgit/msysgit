@echo off
pushd %~dp0
:: Start and set persistent environment variables for SSH agent
for /f %%a in ('cscript.exe /nologo ^"..\etc\start-ssh-agent-persistent.js^" /home') do (
    @set %%a
)
:: Set/reset SSH keys for current SSH agent
for /f "delims=" %%a in ('cscript.exe /nologo ^"..\etc\start-ssh-agent-persistent.js^" /bindir') do (
    call "%%a\ssh-add.exe"
)
popd