#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	echo ""
	echo "You need to have Inno Setup incl. Preprocessor from the QuickStart Pack"
	echo "installed. Please download isetup-5.2.0.exe and ispack-5.2.0.exe from"
	echo "<http://www.jrsoftware.org/isdl.php>."
	exit 1
}

version=$1
TMPDIR=/tmp/WinGit

( echo "Calling WinGit installer to copy files ..." &&
  cd /share/WinGit && ./release.sh $version ) &&
cp gpl-2.0.txt install.bmp $TMPDIR &&
homewinpath=$(cd ~ ; pwd -W) &&
sed -e "s/%APPVERSION%/$version/" -e "s@%OUTPUTDIR%@$homewinpath@" install.iss >$TMPDIR/install.iss &&
echo ""
echo "Inno Setup will now be started for you. After it started you need to" &&
echo "compile the loaded script (4th icon from the left in the toolbar)." &&
echo "After compiling you will find the installer in \"$homewinpath\"." &&
echo ""
echo "NOTE: You should disconnect network drives before lauching Inno Setup." &&
echo ""
echo "Press RETURN to launch Inno Setup." &&
read &&
echo "Lauching Inno Setup ..." &&
/bin/start "$TMPDIR/install.iss"
