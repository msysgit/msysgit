#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	exit 1
}

version=$1
TMPDIR=/tmp/WinGit

/share/WinGit/copy-files.sh $TMPDIR &&
sed "s/msysGit/Git (version $version)/" < /etc/motd > $TMPDIR/etc/motd &&
cp /share/resources/gpl-2.0.rtf /share/resources/git.bmp $TMPDIR &&
homewinpath=$(cd ~ ; pwd -W) &&
sed -e "s/%APPVERSION%/$version/" -e "s@%OUTPUTDIR%@$homewinpath@" \
	< /share/WinGit/install.iss > $TMPDIR/install.iss &&
echo "Lauching Inno Setup compiler ..." &&
/share/InnoSetup/ISCC.exe "$TMPDIR/install.iss"
