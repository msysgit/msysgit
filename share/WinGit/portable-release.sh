#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	exit 1
}

# change directory to msysGit root
SCRIPTDIR="$(cd "$(dirname "$0")" && pwd)"
MSYSGITROOT="$(cd $SCRIPTDIR/../../ && pwd | sed 's/\/$//')/."
cd $MSYSGITROOT || {
	echo "Could not change directory to msysGit root" >&2
	exit 1
}

TARGET="$HOME"/PortableGit-$1.7z
OPTS7="-m0=lzma -mx=9 -md=64M"
TARGET7=tmp.7z
TMPDIR=/tmp/WinGit

DONT_REMOVE_BUILTINS=1 "$(dirname $0)/copy-files.sh" $TMPDIR &&
cd "$TMPDIR" &&
cp $MSYSGITROOT/share/WinGit/README.portable ./ &&
cp $MSYSGITROOT/msys.bat ./git-bash.bat &&
cp $MSYSGITROOT/git-cmd.bat ./ &&
$MSYSGITROOT/share/7-Zip/7za.exe a $OPTS7 $TARGET7 * ||
exit

if test -z "$NO_SFX"
then
(cat $MSYSGITROOT/share/7-Zip/7zSD.sfx &&
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
 cat $TARGET7) > "$TARGET"
else
 mv $TARGET7 "$TARGET"
fi &&
echo "Created $TARGET"
