#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	exit 1
}

TARGET="$HOME"/WinGit-$1.exe
OPTS7="-m0=lzma -mx=9 -md=64M"
TARGET7=tmp.7z
LIST7=fileList.txt
TMPDIR=/tmp/WinGit

(test ! -d "$TMPDIR" || echo "Removing $TMPDIR" && rm -rf "$TMPDIR") &&
mkdir "$TMPDIR" &&
cd "$TMPDIR" &&
echo "Copying files" &&
(cd / && tar cf - bin/ lib/perl5/) |
tar xvf - &&
(cd /mingw && tar cf - bin/*{tcl,tk,wish,gpg,curl.exe}* \
	lib/*{tcl,tk}* libexec/gnupg/) |
tar xvf - &&
mkdir etc &&
cp /etc/profile etc/ &&
cp /share/WinGit/install.tcl ./ &&
: > "$LIST7" &&
find * -type f | sed "s|^\./||" > "$LIST7" &&
7z a $OPTS7 $TARGET7 @"$LIST7" ||
exit

(cat /share/7-Zip/7zSD.sfx &&
 echo ';!@Install@!UTF-8!' &&
 echo 'Progress="yes"' &&
 echo 'Directory="%%T\bin"' &&
 echo 'RunProgram="wish.exe %%T\install.tcl %%T"' &&
 echo ';!@InstallEnd@!7z' &&
 cat $TARGET7) > "$TARGET"
exit

