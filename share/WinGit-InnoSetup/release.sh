#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	exit 1
}

version=$1
TMPDIR=/tmp/WinGit

/share/WinGit/copy-files.sh $TMPDIR &&
cp /share/resources/gpl-2.0.txt /share/resources/git.bmp $TMPDIR &&
homewinpath=$(cd ~ ; pwd -W) &&
sed -e "s/%APPVERSION%/$version/" -e "s@%OUTPUTDIR%@$homewinpath@" install.iss >$TMPDIR/install.iss &&
echo "Lauching Inno Setup compiler ..." &&
/share/InnoSetup/ISCC.exe "$TMPDIR/install.iss"
