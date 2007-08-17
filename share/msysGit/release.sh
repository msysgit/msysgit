#!/bin/sh

case "$1" in
'')
	echo "Usage: $0 <version>"
	exit 1
esac

VERSION="$1"
TARGET="$HOME"/msysGit-$VERSION.exe

case "$(basename "$(cd /; pwd -W)")" in
msysGit) ;;
*)
	echo "Basename of the msysGit directory is not msysGit"
	exit 1
esac

cd "$(dirname "$(cd /; pwd -W)")"

# get list
LIST=list.txt

(cd / &&
 git ls-files | grep -v '^\"\?git/gitweb' &&
 echo "git/gitweb") |
sed "s|^|msysGit/|" > $LIST &&

# make installer
OPTS7="-m0=lzma -mx=9 -md=64M -sfx7z.sfx $TARGET" &&

"$PROGRAMFILES"/7-Zip/7z.exe a $OPTS7 @$LIST
