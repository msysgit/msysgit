@echo off

rem Start the ssh-agent, or make currently running one available
for /f "delims=" %%a in ('git silverkorn') do (
	@set %%a
)
