#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	echo ""
	echo "You need to have installed isetup-5.2.0.exe and ispack-5.2.0.exe"
	echo "from <http://www.jrsoftware.org/isdl.php>."
	exit 1
}

version=$1
TMPDIR=/tmp/WinGit

( echo "calling WinGit installer to copy files." && 
  cd /share/WinGit && ./release.sh $version ) &&
cp gpl-2.0.txt install.bmp $TMPDIR &&
( cd $TMPDIR ; cp etc/fileList-builtins.txt . ) &&
homewinpath=$(cd ~ ; pwd -W) &&
sed -e "s/%VERSION%/$version/" -e "s@%OUTPUTDIR%@$homewinpath@" install.iss >$TMPDIR/install.iss &&
echo "I'll start Inno Installer for you. After it started you need to" &&
echo "'compile' (4th icon in toolbar from left)." &&
echo "After compiling you'll find the installer in $homewinpath." &&
echo "NOTE: you should disconnect network drives before lauching Inno Installer." &&
echo "Press return to launch Inno Installer." &&
read &&
echo "lauching Inno Installer ..." &&
/bin/start $TMPDIR/install.iss
