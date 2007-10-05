#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	exit 1
}

version=$1
TMPDIR=/tmp/WinGit

( echo "Calling WinGit installer to copy files ..." &&
  cd /share/WinGit && ./release.sh $version ) &&
cp gpl-2.0.txt install.bmp $TMPDIR &&
homewinpath=$(cd ~ ; pwd -W) &&
sed -e "s/%APPVERSION%/$version/" -e "s@%OUTPUTDIR%@$homewinpath@" install.iss >$TMPDIR/install.iss &&
echo "Lauching Inno Setup compiler ..." &&
/share/InnoSetup/ISCC.exe "$TMPDIR/install.iss"
