#!/bin/sh

# Recreate GitMe-$VERSION.exe

test -z "$1" && {
	echo "Usage: $0 <version>"
	exit 1
}

TARGET="$HOME"/GitMe-"$1".exe
TMPDIR=/tmp/installer-tmp
OPTS7="-m0=lzma -mx=9 -md=64M"
TMPPACK=/tmp.7z
SHARE=/share/GitMe

test ! -d "$TMPDIR" || rm -rf "$TMPDIR" || exit
mkdir "$TMPDIR" &&
cd "$TMPDIR" &&
(cd .. && test ! -f "$TMPPACK" || rm "$TMPPACK") &&
echo "Copying files" &&
cat "$SHARE"/fileList.txt | (cd / && tar -c --file=- --files-from=-) |
	tar xvf - &&
cat "$SHARE"/fileList-mingw.txt |
	(cd /mingw && tar -c --file=- --files-from=-) |
	tar xvf - &&
strip bin/*.exe &&
mkdir etc &&
cp "$SHARE"/gitconfig etc/ &&
cp "$SHARE"/setup-msysgit.sh ./ &&
echo "Creating archive" &&
cd .. &&
7z a $OPTS7 "$TMPPACK" installer-tmp &&
cat /share/7-Zip/7zSD.sfx "$SHARE"/7z-install.txt "$TMPPACK" > "$TARGET" &&
echo Success! You\'ll find the new installer at $TARGET
rm $TMPPACK
