#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	exit 1
}

TARGET="$HOME"/PortableGit-$1.7z
OPTS7="-m0=lzma -mx=9 -md=64M"
TARGET7=tmp.7z
TMPDIR=/tmp/WinGit

DONT_REMOVE_BUILTINS=1 "$(dirname $0)/copy-files.sh" $TMPDIR &&
cd "$TMPDIR" &&
cp /share/WinGit/README.portable ./ &&
cp /msys.bat ./git-bash.bat &&
cp /git-cmd.bat ./ &&
7z a $OPTS7 $TARGET7 * ||
exit

(cat /share/7-Zip/7zSD.sfx &&
 echo ';!@Install@!UTF-8!' &&
 echo 'Progress="yes"' &&
 echo 'Title="WinGit: MinGW Git + minimal MSys installation"' &&
 echo 'BeginPrompt="This program installs a complete Git for MSys setup"' &&
 echo 'CancelPrompt="Do you want to cancel WinGit installation?"' &&
 echo 'ExtractDialogText="Please, wait..."' &&
 echo 'ExtractPathText="Where do you want to install WinGit?"' &&
 echo 'ExtractTitle="Extracting..."' &&
 echo 'GUIFlags="8+32+64+256+4096"' &&
 echo 'GUIMode="1"' &&
 echo 'InstallPath="%PROGRAMFILES%\\Git"' &&
 echo 'OverwriteMode="0"' &&
 echo ';!@InstallEnd@!7z' &&
 cat $TARGET7) > "$TARGET" &&
echo "Created $TARGET"
