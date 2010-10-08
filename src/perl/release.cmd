@rem Build script for compiling Perl for msysGit
@rem
@rem Perl prefers to be built from a cmd prompt and requires 'dmake'
@rem when using gcc as the compiler.
@rem
@rem You need a copy of sed. Don't add msysGit/bin to the path though
@rem as that breaks the perl build. Grab another from somewhere or
@rem manually fixup the patch file and comment out the sed lines here.
@rem
@rem TODO:
@rem  It would be nice if we could fix the install layout so that it
@rem  matched the msys-perl layout. But this failed when I tried it.
@rem  In the meantime - make a perl shell script that runs the perl
@rem  from mingw/perl/bin/perl so that it gets used instead of /bin/perl
@rem  then we need to fix git-am, git- and the tests that use perl
@rem  File::Spec::Functions should be useful.
@rem
@setlocal

@for /F "delims=" %%I in ("%~dp0.") do @set BASE=%%~fI
@for /F "delims=" %%I in ("%~dp0..\..") do @set ROOT=%%~fI
@set PATH=%ROOT%\mingw\bin;%PATH%
@set ZIP=%ROOT%\share\7-zip\7za.exe >NUL
@set URL=http://www.cpan.org/src/5.0
@set VER=5.12.2
@set MD5=af2df531d46b77fdf0d97eecb03eddb2
@set DMAKE=dmake-4.12-20090907-SHAY.zip
@set DMAKEMD5=6a68a9d456df62808d798bd8710ce091

:DOWNLOADPERL
@if exist perl-%VER%.tar.gz @goto CHECKSUMPERL
@echo Downloading perl from %URL%
@curl -o perl-%VER%.tar.gz %URL%/perl-%VER%.tar.gz

:CHECKSUMPERL
@echo %MD5% *perl-%VER%.tar.gz | md5sum >NUL --check -
@if ERRORLEVEL 0 @goto DOWNLOADDMAKE
@echo error: incorrect checksum for perl file
@goto EXIT

:DOWNLOADDMAKE
@if exist %DMAKE% @goto CHECKSUMDMAKE
@echo Downloading dmake
@curl -o %DMAKE% http://search.cpan.org/CPAN/authors/id/S/SH/SHAY/%DMAKE%

:CHECKSUMDMAKE
@echo %DMAKEMD5% *%DMAKE% | md5sum >NUL --check -
@if ERRORLEVEL 0 @goto UNPACKDMAKE
@echo error: incorrect checksum for dmake file
@goto EXIT

:UNPACKDMAKE
@if exist dmake @goto UNPACK
@if not exist dmake %ZIP% x %DMAKE%

:UNPACK
@if exist perl-%VER% goto CLEAN
@if not exist perl-%VER%.tar %ZIP% x perl-%VER%.tar.gz
@if not exist perl-%VER% %ZIP% x perl-%VER%.tar
@if ERRORLEVEL 0 (
  @pushd perl-%VER%
  @cmd /c git init
  @cmd /c git config core.autocrlf true
  @cmd /c git add . 2>NUL
  @cmd /c git commit -m "Imported perl-%VER%" 2>NUL
  @cmd /c git rm -rf . >NUL
  @cmd /c git reset --hard HEAD
)
@popd

:CLEAN
@pushd perl-%VER%
@cmd /c git reset --hard HEAD
@cmd /c git clean -fd
@popd

:PATCH
@sed -e "s/@ROOT@/%ROOT:\=\\%/" patches\makefile.patch > fixed.patch
@dos2unix fixed.patch
@pushd perl-%VER%
@cmd /c git apply ../fixed.patch
@popd

:COMPILE
@pushd perl-%VER%\win32
@%BASE%\dmake\dmake install
@popd
@del %ROOT%\bin\perl.exe
@echo #!/bin/sh                 >  %ROOT%\bin\perl
@echo /mingw/perl/bin/perl "$@" >> %ROOT%\bin\perl

:EXIT