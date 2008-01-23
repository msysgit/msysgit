@echo off
rem Copyright (C):  2001, 2002  Earnie Boyd
rem   mailto:earnie@users.sf.net
rem This file is part of Minimal SYStem
rem   http://www.mingw.org/msys.shtml
rem
rem File:	    msys.bat
rem Revision:	    2.0
rem Revision Date:  April 17th, 2002

rem DON'T CHANGE the value of CYGWIN.
rem Ok.  Go ahead change it.  Just don't cry on my list if you do.
set CYGWIN="nowinsymlinks notty notitle binmode nontsec nontea nosmbntsec"

rem ember to set the "Start in:" field of the shortcut.
rem A value similar to C:\msys\1.0\bin is what the "Start in:" field needs
rem to represent.

if "x%MSYSTEM%" == "x" set MSYSTEM=MINGW32
if "%1" == "MSYS" set MSYSTEM=MSYS

if NOT "x%DISPLAY%" == "x" set DISPLAY=

rem Setup the default colors for rxvt.
if "x%MSYSBGCOLOR%" == "x" set MSYSBGCOLOR=White
if "x%MSYSFGCOLOR%" == "x" set MSYSFGCOLOR=Black
if "x%MINGW32BGCOLOR%" == "x" set MINGW32BGCOLOR=LightYellow
if "x%MINGW32FGCOLOR%" == "x" set MINGW32FGCOLOR=Navy
if "%MSYSTEM%" == "MSYS" set BGCOLOR=%MSYSBGCOLOR%
if "%MSYSTEM%" == "MSYS" set FGCOLOR=%MSYSFGCOLOR%
if "%MSYSTEM%" == "MINGW32" set BGCOLOR=%MINGW32BGCOLOR%
if "%MSYSTEM%" == "MINGW32" set FGCOLOR=%MINGW32FGCOLOR%

if EXIST bin cd bin
if EXIST rxvt.exe goto startrxvt
if EXIST sh.exe goto startsh

echo Cannot find the rxvt.exe or sh.exe binary -- aborting.
pause
exit 1

rem If you don't want to use rxvt then rename the file rxvt.exe to something
rem else.  Then sh.exe will be used instead.
:startrxvt
start rxvt -sl 2500 -fg %FGCOLOR% -bg %BGCOLOR% -sr -fn Courier-12 -tn msys -e /bin/sh --login -i
exit

:startsh
start sh --login -i
exit

rem ChangeLog:
rem 2002.03.07  Earnie Boyd  mailto:earnie@users.sf.net
rem	* Move the @echo off to the top.
rem	* Change the binmode setting to nobinmode.
rem     * Remove the angle brackets around email address to workaround MS 
rem	buggy command processor.
rem
rem 2002.03.12  Earnie Boyd  mailto:earnie@users.sf.net
rem	* Add filter logic to find rxvt.exe
rem
rem 2002.03.13  Earnie Boyd  mailto:earnie@users.sf.net
rem	* Revert the nobinmode change.
rem
rem 2002.03.20  Earnie Boyd  mailto:earnie@users.sf.net
rem     * Add logic for stating bash.
rem
rem 2002.04.11  Earnie Boyd  mailto;earnie@users.sf.net
rem	* Add logic for setting MSYSTEM value based on parameter.
rem
rem 2002.04.15  Olivier Gautherot  mailto:olivier_gautherot@mentorg.com
rem	* Reduce number test conditions for finding an executable.
rem
rem 2002.04.15  Earnie Boyd  mailto:earnie@users.sf.net
rem	* Unset DISPLAY if set before starting shell.
rem
rem 2002.04.16  Earnie Boyd  mailto:earnie@users.sf.net
rem	* Remove use of DEFINED in conditional statments for variables for
rem	command.com support.
rem	* Add check for nonexistance of USERNAME variable for Win9x support.
rem
rem 2002.04.17  Earnie Boyd  mailto:earnie@users.sf.net
rem	* Add foreground and background color defaults based on MSYSTEM value.
rem
rem 2002.04.22  Earnie Boyd  mailto:earnie@users.sf.net
rem	* More Win 9x changes.
rem
rem 2002.05.04  Earnie Boyd  mailto:earnie@users.sf.net
rem	* Remove the SET of USERNAME and HOME.
rem
