#!/bin/sh

case "$1" in
'')
	echo "Usage: $0 <version>"
	exit 1
esac

VERSION="$1"
TARGET="$HOME"/msysGit-fullinstall-$VERSION.exe

case "$(basename "$(cd /; pwd -W)")" in
msysGit|msysgit) ;;
*)
	echo "Basename of the msysGit directory is not msysGit"
	exit 1
esac

cd "$(dirname "$(cd /; pwd -W)")"

# get list
LIST=list.txt

git --git-dir=/.git rev-parse --verify HEAD > /etc/full-msysgit-sha1 &&
git --git-dir=/git/.git rev-parse --verify HEAD > /etc/full-git-sha1 || {
	echo "Could not get the current SHA-1s" >&2
	exit 1
}

(cd / &&
 echo etc/full-msysgit-sha1 &&
 echo etc/full-git-sha1 &&
 git ls-files | grep -ve "^git$" -e "^doc/git/html$" &&
 (cd doc/git/html && git ls-files | sed 's|^|doc/git/html/|') &&
 cd git && git ls-files | grep -v '^\"\?gitweb' | sed 's|^|git/|' &&
 echo "git/gitweb") |
sed "s|^|msysGit/|" > $LIST &&

# make installer
test -f "$TARGET".7z && rm "$TARGET".7z
OPTS7="-m0=lzma -mx=9 -md=64M" &&
/share/7-Zip/7za.exe a $OPTS7 "$TARGET".7z @$LIST &&

(cat /share/7-Zip/7zSD.sfx &&
 echo ';!@Install@!UTF-8!' &&
 echo 'Progress="yes"' &&
 echo 'Title="GitMe: MinGW Git + MSys installation"' &&
 echo 'BeginPrompt="This archive contains the complete system needed to\nbootstrap the latest MinGW Git and MSys environment"' &&
 echo 'CancelPrompt="Do you want to cancel MSysGit installation?"' &&
 echo 'ExtractDialogText="Please, wait..."' &&
 echo 'ExtractPathText="Where do you want to install MSysGit?"' &&
 echo 'ExtractTitle="Extracting..."' &&
 echo 'GUIFlags="8+32+64+256+4096"' &&
 echo 'GUIMode="1"' &&
 echo 'InstallPath="C:\\msysgit"' &&
 echo 'OverwriteMode="2"' &&
 echo 'RunProgram="\"%%T\\msysGit\\bin\\sh.exe\" --login -i"' &&
 echo ';!@InstallEnd@!7z' &&
 cat "$TARGET".7z) > "$TARGET" &&
echo "Success! You'll find the new installer at \"$TARGET\"." &&
rm "$TARGET".7z
